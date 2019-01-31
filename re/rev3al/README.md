# Reveal

Flag: `wh3N1TsD4rk0ut`

Description: `qemu is for n00bs. Ours is the real deal!`

Reverse the switch cases to figure out which opcode in `chal.o.1` and `chal.o.2` corresponds to which case of the decoder. Each opcode is 32 bits in size. Each instruction contains contains 1 byte which corresponds to a switch case and 2 bytes which correspond to 2 operands.

Other way is to just figure out which one of the cases corresponds to loading the source buffer's index into a vm register for validation. The vm registers are stored in the .bss segment (`r0`, `r1`, `r2` are general purpose registers, `r3` is the instruction pointer and `r4` is a flag which is used to toggle variants of the vm opcodes). All registers are 1 byte large.

Since the input buffer is stored at an offset of 200 to the vm's memory region, index 0 corresponds to 200.

The following corresponds to case 5 which is responsible for the load instruction: 
```
ld r0 r1
```
will copy `r1` into `r0` if `r4` is not set. This corresponds to `mov eax ebx` in `x86`. If `r4` is set, this corresponds to `mov eax, BYTE PTR [ebx]`

```assembly
gdb-peda$ x/20i 0x555555555b07
   0x555555555b07 <_Z6decodej+378>: mov    rax,QWORD PTR [rip+0x201872]        # 0x555555757380 <reg>
   0x555555555b0e <_Z6decodej+385>: cmp    BYTE PTR [rax+0x4],0x0
   0x555555555b12 <_Z6decodej+389>: je     0x555555555b39 <_Z6decodej+428>
   0x555555555b14 <_Z6decodej+391>: movzx  edi,dil
   0x555555555b18 <_Z6decodej+395>: movzx  ecx,BYTE PTR [rax+rdi*1]
   0x555555555b1c <_Z6decodej+399>: mov    rsi,QWORD PTR [rip+0x20187d]        # 0x5555557573a0 <MEM>
   0x555555555b23 <_Z6decodej+406>: movzx  ecx,BYTE PTR [rsi+rcx*1]
   0x555555555b27 <_Z6decodej+410>: movzx  edx,dl
   0x555555555b2a <_Z6decodej+413>: mov    BYTE PTR [rax+rdx*1],cl
   0x555555555b2d <_Z6decodej+416>: mov    rax,QWORD PTR [rip+0x20184c]        # 0x555555757380 <reg>
   0x555555555b34 <_Z6decodej+423>: add    BYTE PTR [rax+0x3],0x1
...
```

Eg:
```assembly
...
RCX: 0xd5
...
=> 0x555555555b23 <_Z6decodej+406>: movzx  ecx,BYTE PTR [rsi+rcx*1]
...
```
`0xd5 = 213` so this specific case is comparing 13'th index of the input.

If the order of the indices is figured out, the flag can be brute forced by counting the number of instructions/basic-blocks executed for each character using a Pin tool.

Sample solution:

Pin tool:
```cpp
...
VOID docount() {
    bblCount++;
}

VOID image(IMG img, VOID *v) {
    if (!IMG_IsMainExecutable(img))
        return;
    main_low = IMG_LowAddress(img);
    main_high = IMG_HighAddress(img);
}

VOID trace(TRACE trace, VOID *v) {
    ADDRINT trace_address = TRACE_Address(trace);
    if (trace_address >= main_low && trace_address <= main_high) {
        for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl))
            BBL_InsertCall(bbl, IPOINT_BEFORE, (AFUNPTR)docount, IARG_UINT32, BBL_NumIns(bbl), IARG_END);
    }
}
```

Runner script:
```python
PIN = '/home/vagrant/tools/pin-3.7-97619-g0d0c92f4f-gcc-linux/pin'
TOOL = '/home/vagrant/tools/pin-3.7-97619-g0d0c92f4f-gcc-linux/source/tools/rev3al/obj-intel64/reveal.so'
CHAL = './vm'
CMD = [PIN, '-t', TOOL, '--', CHAL]
alphabet = string.letters + string.digits


def generate_input(done, i, char):
    default = 'a'
    n = 14
    data = [default] * n
    for idx in done:
        data[idx] = done[idx]
    data[i] = char
    data = ''.join(data)
    sys.stdout.write(data + '\r')
    sys.stdout.flush()
    return data

p = Popen(CMD, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
stdout = p.communicate(input='aaaa')[0].split('\n')[1]
max_ins = int(stdout)

order = [0, 4, 13, 1, 7, 3, 10, 5, 11, 6, 12, 2, 8]
done = {}

for idx in order:
    for c in alphabet:
        data = generate_input(done, idx, c)
        p = Popen(CMD, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
        stdout = p.communicate(input=data)[0].split('\n')[1]
        if p.returncode == 0:
            print '\nFound flag:'
            print 'hackim19{%s}' % data
            sys.exit(0)
        ins = int(stdout)
        if ins > max_ins:
            max_ins = ins
            done[idx] = c
            break
```

Output:
```bash
vagrant@amy:~/tools/pin-3.7-97619-g0d0c92f4f-gcc-linux/source/tools/rev3al$ python sol.py
wh3N1TsD4ak0ut
Found flag:
hackim19{wh3N1TsD4ak0ut}
```

Complete source files are present in the solution directory!
