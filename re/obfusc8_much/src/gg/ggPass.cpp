#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/RandomNumberGenerator.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include <time.h>

#include <unordered_set>
using namespace llvm;

static cl::opt<int> level("level", cl::desc("levels to obfuscate"),
                          cl::value_desc("filename"));

namespace {
struct Obfuscate : public FunctionPass {
    static char ID;
    Obfuscate() : FunctionPass(ID) {}

    static Value *Add1(Instruction *I, BasicBlock *BB) {
        Value *op1 = I->getOperand(0);
        Value *op2 = I->getOperand(1);

        BinaryOperator *substitute = nullptr;

        Type *type = I->getType();
        auto rand_value = ConstantInt::get(type, rand());

        substitute = BinaryOperator::Create(Instruction::Add, op1, rand_value,
                                            "op1+rand", BB);
        substitute = BinaryOperator::Create(Instruction::Add, substitute, op2,
                                            "op1+rand+op2", BB);
        substitute = BinaryOperator::Create(
            Instruction::Sub, substitute, rand_value, "op1+rand+op2-rand", BB);

        return substitute;
    }

    static Value *Sub1(Instruction *I, BasicBlock *BB) {
        Value *op1 = I->getOperand(0);
        Value *op2 = I->getOperand(1);

        BinaryOperator *substitute = nullptr;

        Type *type = I->getType();
        auto rand_value = ConstantInt::get(type, rand());

        substitute = BinaryOperator::Create(Instruction::Add, op1, rand_value,
                                            "op1+rand", BB);
        substitute = BinaryOperator::Create(Instruction::Sub, substitute, op2,
                                            "op1+rand-op2", BB);
        substitute = BinaryOperator::Create(
            Instruction::Sub, substitute, rand_value, "op1+rand-op2-rand", BB);

        return substitute;
    }

    static Value *Add2(Instruction *I, BasicBlock *BB) {
        Value *op1 = I->getOperand(0);
        Value *op2 = I->getOperand(1);

        BinaryOperator *substitute = nullptr;
        BinaryOperator *negOp1 = nullptr;
        BinaryOperator *negOp2 = nullptr;

        Type *type = I->getType();

        negOp1 = BinaryOperator::CreateNeg(op1, "-op1", BB);
        negOp2 = BinaryOperator::CreateNeg(op2, "-op2", BB);

        substitute = BinaryOperator::Create(Instruction::Add, negOp1, negOp2,
                                            "-op1-op2", BB);
        substitute = BinaryOperator::CreateNeg(substitute, "-(-op1-op2)", BB);

        return substitute;
    }

    static Value *Sub2(Instruction *I, BasicBlock *BB) {
        Value *op1 = I->getOperand(0);
        Value *op2 = I->getOperand(1);

        BinaryOperator *substitute = nullptr;
        BinaryOperator *negOp1 = nullptr;
        BinaryOperator *negOp2 = nullptr;

        Type *type = I->getType();

        negOp1 = BinaryOperator::CreateNeg(op1, "-op1", BB);
        negOp2 = BinaryOperator::CreateNeg(op2, "-op2", BB);

        substitute = BinaryOperator::Create(Instruction::Sub, negOp1, negOp2,
                                            "-op1-(-op2)", BB);
        substitute =
            BinaryOperator::CreateNeg(substitute, "-(-op1-(-op2))", BB);

        return substitute;
    }

    static Value *Xor(Instruction *I, BasicBlock *BB) {
        Value *op1 = I->getOperand(0);
        Value *op2 = I->getOperand(1);

        BinaryOperator *substitute = nullptr;
        BinaryOperator *substitute1 = nullptr;

        substitute = BinaryOperator::CreateNot(op1, "~op1", BB);
        substitute = BinaryOperator::Create(Instruction::And, op2, substitute,
                                            "op2&(~op1)", BB);

        substitute1 = BinaryOperator::CreateNot(op2, "~op2", BB);
        substitute1 = BinaryOperator::Create(Instruction::And, op1, substitute1,
                                             "op1&(~op2)", BB);
        substitute =
            BinaryOperator::Create(Instruction::Or, substitute, substitute1,
                                   "op2&(~op1)|op1&(~op2)", BB);

        return substitute;
    }

    static Value *Or1(Instruction *I, BasicBlock *BB) {
        Type *ty = I->getType();
        ConstantInt *co = (ConstantInt *)ConstantInt::get(ty, rand());

        BinaryOperator *op =
            BinaryOperator::CreateNot(I->getOperand(0), "", BB);
        BinaryOperator *op1 =
            BinaryOperator::CreateNot(I->getOperand(1), "", BB);
        BinaryOperator *op2 = BinaryOperator::CreateNot(co, "", BB);
        BinaryOperator *op3 =
            BinaryOperator::Create(Instruction::And, op, co, "", BB);
        BinaryOperator *op4 = BinaryOperator::Create(
            Instruction::And, I->getOperand(0), op2, "", BB);
        BinaryOperator *op5 =
            BinaryOperator::Create(Instruction::And, op1, co, "", BB);
        BinaryOperator *op6 = BinaryOperator::Create(
            Instruction::And, I->getOperand(1), op2, "", BB);
        op3 = BinaryOperator::Create(Instruction::Or, op3, op4, "", BB);
        op4 = BinaryOperator::Create(Instruction::Or, op5, op6, "", BB);
        op5 = BinaryOperator::Create(Instruction::Xor, op3, op4, "", BB);
        op3 = BinaryOperator::Create(Instruction::Or, op, op1, "", BB);
        op3 = BinaryOperator::CreateNot(op3, "", BB);
        op4 = BinaryOperator::Create(Instruction::Or, co, op2, "", BB);
        op4 = BinaryOperator::Create(Instruction::And, op3, op4, "", BB);
        op = BinaryOperator::Create(Instruction::Or, op5, op4, "", BB);
        return op;
    }

    static Value *Or2(Instruction *I, BasicBlock *BB) {
        BinaryOperator *op = NULL;
        op = BinaryOperator::Create(Instruction::And, I->getOperand(0),
                                    I->getOperand(1), "", BB);
        BinaryOperator *op1 = BinaryOperator::Create(
            Instruction::Xor, I->getOperand(0), I->getOperand(1), "", BB);

        op = BinaryOperator::Create(Instruction::Or, op, op1, "", BB);
        return op;
    }

    // Adds a switch with a dummy loop, second param is a list of functions
    // which replace an instruction
    void AddSwitch(Instruction *I,
                   Value *(*genfnc[3])(Instruction *, BasicBlock *)) {
        Value *op1 = I->getOperand(0);
        Value *op2 = I->getOperand(1);

        auto F = I->getFunction();
        auto BB = I->getParent();

        Type *type = I->getType();
        IRBuilder<> *builder = new IRBuilder<>(I);

        // A place on the stack to store values from all the paths in the
        // switch.
        Value *substitute =
            builder->CreateAlloca(Type::getInt32Ty(F->getContext()));

        auto two = ConstantInt::get(type, 2);
        auto zero_c = ConstantInt::get(Type::getInt32Ty(I->getContext()), 0);
        ;
        auto one_c = ConstantInt::get(Type::getInt32Ty(I->getContext()), 1);
        ;

        BasicBlock *swDefault =
            BasicBlock::Create(F->getContext(), "defaultCase", F);
        BasicBlock *zeroCase =
            BasicBlock::Create(F->getContext(), "zeroCase", F);
        BasicBlock *oneCase = BasicBlock::Create(F->getContext(), "oneCase", F);

        // Create op1%2 check
        builder->SetInsertPoint(I);
        auto checkCond = builder->CreateURem(op1, two);

        // create switch for op1%2
        builder->SetInsertPoint(I);
        auto switch_main = builder->CreateSwitch(checkCond, swDefault, 2);
        switch_main->addCase(zero_c, zeroCase);
        switch_main->addCase(one_c, oneCase);

        // split at the instruction and switch to create loop
        auto N = BB->splitBasicBlock(I);
        auto S = BB->splitBasicBlock(switch_main);

        // default case. never hit. dummy loop
        builder->SetInsertPoint(swDefault);
        builder->CreateStore(genfnc[0](I, swDefault), substitute);
        builder->CreateBr(S);

        // use one of the obfuscators to generate a substitiue instruction
        builder->SetInsertPoint(zeroCase);
        builder->CreateStore(genfnc[1](I, zeroCase), substitute);
        builder->CreateBr(N);

        builder->SetInsertPoint(oneCase);
        builder->CreateStore(genfnc[2](I, oneCase), substitute);
        builder->CreateBr(N);

        // really?
        swDefault->moveBefore(N);
        zeroCase->moveBefore(N);
        oneCase->moveBefore(N);

        // load the stack variable and replace the occurence of result with it
        BasicBlock::iterator DI = N->begin();
        Instruction &Inst = *DI;
        builder->SetInsertPoint(&Inst);
        Value *checker = builder->CreateLoad(substitute);
        I->replaceAllUsesWith(checker);

        // remove dummy jump and original instruction
        S->getTerminator()->eraseFromParent();
        I->eraseFromParent();
    }

    bool runOnFunction(Function &F) override {
        srand(time(0));

        int obfuscated = 0;

        Value *(*xorfnc[3])(Instruction *, BasicBlock *) = {Xor, Xor, Xor};
        Value *(*addfnc[3])(Instruction *, BasicBlock *) = {Add1, Add2, Add1};
        Value *(*subfnc[3])(Instruction *, BasicBlock *) = {Sub1, Sub2, Sub1};
        Value *(*orfnc[3])(Instruction *, BasicBlock *) = {Or1, Or2, Or1};

        // errs() << "Obfuscate: ";
        errs().write_escaped(F.getName()) << '\n';
        // errs() << "Before : \n";
        // F.print(errs());
        // errs().write_escaped(F.getName()) << '\n';

        // iterate over instructions and replace suitable ones
        std::vector<Instruction *> toDoAdd, toDoSub, toDoOr, toDoXor;

        while(obfuscated < level){
            errs() << "Round : " << obfuscated << "/" << level << "\n";
            toDoAdd.clear();
            toDoSub.clear();
            toDoOr.clear();
            toDoXor.clear();
            for (Function::iterator bb = F.begin(); bb != F.end(); ++bb) {
                for (BasicBlock::iterator I = bb->begin(); I != bb->end(); ++I) {
                    // I->print(errs() << "\n");
                    if (I->getOpcode() == BinaryOperator::Xor) {
                        auto &ins = *I;
                        toDoXor.push_back(&ins);
                        obfuscated++;
                        break;
                    }
                    if (I->getOpcode() == BinaryOperator::Add) {
                        auto &ins = *I;
                        toDoAdd.push_back(&ins);
                        obfuscated++;
                        break;
                    }
                    if (I->getOpcode() == BinaryOperator::Sub) {
                        auto &ins = *I;
                        toDoSub.push_back(&ins);
                        obfuscated++;
                        break;
                    }
                    if (I->getOpcode() == BinaryOperator::Or) {
                        auto &ins = *I;
                        toDoOr.push_back(&ins);
                        obfuscated++;
                        break;
                    }
                    if (obfuscated > level) {
                        break;
                    }
                }
                if (obfuscated > level) {
                    break;
                }
            }

            for (auto &I : toDoAdd) {
                AddSwitch(cast<Instruction>(I), addfnc);
            }

            for (auto &I : toDoSub) {
                AddSwitch(cast<Instruction>(I), subfnc);
            }

            for (auto &I : toDoOr) {
                AddSwitch(cast<Instruction>(I), orfnc);
            }

            for (auto &I : toDoXor) {
                AddSwitch(cast<Instruction>(I), xorfnc);
            }

            // errs() << "After : \n";
            // F.print(errs());
        }
        return obfuscated;
    }
};
} // namespace

char Obfuscate::ID = 0;
static RegisterPass<Obfuscate> X("obfuscate", "obfuscate");