/*
 * gg.c
 *
 * Copyright 2018 Sudhakar Verma <sudhakar@payatu.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_SIZE (0x4000 & ~(getpagesize() - 1))

static void setup(void) __attribute__((constructor));

int putchr(char out) { return write(1, &out, 1); }

void dump(const char *filename) {
    char c;
    FILE *flag;
    flag = fopen(filename, "r");
    if(!flag)
        perror("fgets");
    do {
        c = fgetc(flag);
        putchr(c);
    } while (c != EOF);
}

void put(const char *out) {
    while (*out) {
        putchr(*(out++));
    }
}

static long forbidden_syscalls[] = {SYS_execve};

#define forbidden_syscalls_len                                                 \
    ((sizeof(forbidden_syscalls) / sizeof(forbidden_syscalls[0])))

static void setup() {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    assert(prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == 0);

    struct sock_filter instrs[forbidden_syscalls_len + 5];
#define NUM_INSTRS (sizeof(instrs) / sizeof(instrs[0]))
#define FAIL_IDX (NUM_INSTRS - 1)
#define ACCEPT_IDX (NUM_INSTRS - 2)
    instrs[0] = (struct sock_filter)BPF_STMT(
        BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, arch));
    unsigned int my_arch =
#ifdef __x86_64__
        AUDIT_ARCH_X86_64
#else
#error unknown architecture
#endif
        ;
    instrs[1] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, my_arch,
                                             0, FAIL_IDX - (1 + 1));
    instrs[2] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                                             offsetof(struct seccomp_data, nr));
    for (int i = 0; i < forbidden_syscalls_len; i++) {
        instrs[i + 3] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                                     forbidden_syscalls[i],
                                                     FAIL_IDX - (i + 3 + 1), 0);
    }
    instrs[ACCEPT_IDX] =
        (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW);
    instrs[FAIL_IDX] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K,
                                                    SECCOMP_RET_ERRNO | 0x1234);
    struct sock_fprog fprog = {.len = NUM_INSTRS, .filter = instrs};

    assert(prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &fprog, 0, 0) == 0);
}

int main(int argc, char **argv) {
    int fd, i, count;
    char *psc, *c;
    void (*f)();
    psc = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert(psc != NULL);
    fflush(stdout);
    f = (void (*)())psc;

    while (1) {
        c = psc;
        count = read(0, psc, BUF_SIZE);
        *(c + count) = '\xc3';
        while (count--) {
            if (!isalpha(*(c + count)) && !isdigit(*(c + count))) {
                put("Epic Fail!");
                exit(-1);
            }
        }
        f();
    }
    return 0;
}