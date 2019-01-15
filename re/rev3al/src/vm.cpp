#include <iostream>
#include <vector>
#include <fstream>
#include <sys/mman.h>
#include <cstring>

std::string p1 = "chal.o.1";
std::string p2 = "chal.o.2";

#define PAGESIZE 256
#define REGCOUNT 5              // r0, r1, r2, ip, m
#define r0 0
#define r1 1
#define r2 2
#define ip 3                    // instruction pointer
#define m 4                     // if this is set then registers store addresses

uint32_t *TEXT = NULL;
uint8_t *MEM = NULL;
uint32_t *JMP = NULL;
std::vector<uint8_t> reg;
bool running = true;

void decode(uint32_t);
void run();
void read_text(std::string);

int main(int argc, char *argv[]) {
    TEXT = (uint32_t*)mmap(NULL, PAGESIZE * 10, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, 0, 0);
    if (TEXT == MAP_FAILED) {
        std::cerr << "Failed to allocate .text segment\n";
        exit(1);
    }

    MEM = (uint8_t*)mmap(NULL, PAGESIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, 0, 0);
    if (MEM == MAP_FAILED) {
        std::cerr << "Failed to allocate .mem segment\n";
        exit(1);
    }

    JMP = (uint32_t*)mmap(NULL, PAGESIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, 0, 0);
    if (TEXT == MAP_FAILED) {
        std::cerr << "Failed to allocate jump table\n";
        exit(1);
    }

    std::string s;
    size_t n = 14;
    std::cout << "Go for it:\n";
    std::cin >> s;
    if (s.length() == 0 || s.length() > 14)
        exit(1);

    memset((void*)MEM, 0, PAGESIZE);
    memset((void*)JMP, 0, PAGESIZE);
    memcpy(MEM+200, s.c_str(), n);
    for (unsigned int i = 0; i < REGCOUNT; i++) {
        reg.push_back(0);
    }

    reg[ip] = 0;
    read_text(p1);
    run();
    if (MEM[1]) {
        reg[ip] = 0;
        read_text(p2);
        run();
    }

    reg.clear();
    if (MEM[2]) {
        std::cout << "Well done\n";
        std::exit(0);
    }
    std::exit(1);
}

void read_text(std::string path) {
    memset((void*)TEXT, 0, PAGESIZE);
    std::ifstream in(path, std::ios::binary);
    long length = 0;
    if (in) {
        in.seekg(0, in.end);
        length = in.tellg();
        in.seekg(0, in.beg);
    }
    else {
        std::cerr << "Failed to open file\n";
        exit(1);
    }
    in.read((char*)TEXT, length);
}

void run() {
    uint32_t *ins = TEXT;
    unsigned int counter = 0;
    // populate JUMP table
    for (unsigned int j = 0; counter < (PAGESIZE / sizeof(uint32_t)) && j < (PAGESIZE / sizeof(uint32_t)); counter++) {
        uint8_t operation = (TEXT[counter] & 0xf0000) >> 16;
        if (operation == 0xc)
            JMP[j++] = counter;
    }

    running = true;
    while (running) {
        decode(ins[reg[ip]]);
    }
}

void decode(uint32_t instruction) {
    // -------- (4 byte instructions)
    uint8_t operation = (instruction & 0xf0000) >> 16;
    uint8_t op1 = (instruction & 0x3);
    uint8_t op2 = (instruction & 0xc) >> 2;
    if (op1 == 3)
        op1 = 2;
    if (op2 == 3)
        op2 = 2;

    switch (operation) {
        case 0x0: // halt
            running = false;
            break;
        case 0x1: // add
            if (reg[m])
                reg[op1] = MEM[reg[op1]] + MEM[reg[op2]];
            else
                reg[op1] = reg[op1] + reg[op2];
            reg[ip]++;
            break;
        case 0x2: // sub
            if (reg[m])
                reg[op1] = MEM[reg[op1]] - MEM[reg[op2]];
            else
                reg[op1] = reg[op1] - reg[op2];
            reg[ip]++;
            break;
        case 0x3: // multiply
            if (reg[m])
                reg[op1] = MEM[reg[op1]] * MEM[reg[op2]];
            else
                reg[op1] = reg[op1] * reg[op2];
            reg[ip]++;
            break;
        case 0x4: // divide
            if (reg[m])
                reg[op1] = MEM[reg[op1]] / MEM[reg[op2]];
            else
                reg[op1] = reg[op1] / reg[op2];
            reg[ip]++;
            break;
        case 0x5: // load
            if (reg[m])
                reg[op1] = MEM[reg[op2]];
            else
                reg[op1] = reg[op2];
            reg[ip]++;
            break;
        case 0x6: // store
            if (reg[m])
                MEM[reg[op1]] = MEM[reg[op2]];
            else
                MEM[reg[op1]] = reg[op2];
            reg[ip]++;
            break;
        case 0x7: // jump
            reg[ip] = reg[op1];
            break;
        case 0x8: // change mode
            reg[m] = (~reg[m]) & 1;
            reg[ip]++;
            break;
        case 0x9: // jump if zero
            if (reg[op1] == 0) {
                if (reg[m])
                    reg[ip] += reg[op2];
                else
                    reg[ip] = reg[op2];
            }
            else
                reg[ip]++;
            break;
        case 0xa: // set register
            reg[op1] = op2;
            reg[ip]++;
            break;
        case 0xb: // increment
            if (reg[m])
                MEM[reg[op1]]++;
            else
                reg[op1]++;
            reg[ip]++;
            break;
        case 0xc: // mark
            reg[ip]++;
            break;
        default:
            std::cerr << "Invalid instruction!\n";
            exit(1);
            break;
    }
}
