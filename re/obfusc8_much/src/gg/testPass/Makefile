CC = /home/sudhakar/tools/llvm/build/bin/clang
OPT = /home/sudhakar/tools/llvm/build/bin/opt
LLVMDIS = /home/sudhakar/tools/llvm/build/bin/llvm-dis
LEVEL?=10

all: test-full dist-full
test-full: testbc checktest
dist-full: distbc checkdist

distbc: dist.bc
testbc: test.bc

checkdist: dist
checktest: test

%.bc: %.c
	$(CC) -emit-llvm -c $< -o $@
	$(LLVMDIS) $@

check% : %
	$(OPT) -O0 -load ../build/lib/LLVMgg.so -obfuscate -level $(LEVEL) $<.bc -o $<-out.bc
	$(CC) -mllvm -disable-llvm-optzns -O0 -o $< $<-out.bc

clean:
	rm -rf *.bc *.ll dist test
