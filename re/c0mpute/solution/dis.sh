#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "[-] Usage: $0 <opencl binary> <.ocl.obj section start> <.ocl.obj section size>"
    readelf -S $1
    exit 1
fi

echo "[*] This will get the x86_64 binary object from the OpenCL kernel so"
echo "    that is can be disassembled with objdump/ida/..."

start_addr=$((0x$2))
size=$((0x$3))

dd skip=$start_addr count=$size if=$1 of=oclobj.bin bs=1
objdump -M intel -d -m i386:x86-64 oclobj.bin

echo "[+] Saved as oclobj.bin"
