import struct
import sys

instructions = {
    'hlt' : 0x0,
    'add'  : 0x1,
    'sub'  : 0x2,
    'mul'  : 0x3,
    'div'  : 0x4,
    'ld'   : 0x5,
    'str'  : 0x6,
    'jmp'  : 0x7,
    'chm'  : 0x8,
    'je'   : 0x9,
    'sr'   : 0xa,
    'inc'  : 0xb,
    'mark' : 0xc,
    'jm'   : 0xd
}

regs = {
    'r0': 0,
    'r1': 1,
    'r2': 2
}

if len(sys.argv) < 3:
    print('Usage: {} <infile> <outfile>'.format(sys.argv[0]))
    sys.exit()

infile = sys.argv[1]
outfile = sys.argv[2]

OP_MAX = 2

shellcode = ''
with open(infile) as f:
    for l in f:
        if l.startswith('#') or l == '\n':
            continue
        line = l.split()
        ins = line[0]
        op_a = 0
        op_b = 0
        if len(line) > 1:
            op_a = line[1]
            if op_a in regs:
                op_a = regs[op_a]
            op_a = int(op_a)
        if len(line) > 2:
            op_b = line[2]
            if op_b in regs:
                op_b = regs[op_b]
            op_b = int(op_b)

        assert(op_a >= 0 and op_a <= OP_MAX)
        assert(op_b >= 0 and op_b <= OP_MAX)
        assert(ins in instructions)
        ins = instructions[ins]

        code = ins << 16
        code += op_a
        code += op_b << 2

        shellcode += struct.pack('<I', code)

with open(outfile, 'wb') as f:
    f.write(shellcode)
