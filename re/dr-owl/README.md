#### Dr Owl

##### Description

TBD

##### Points

100/150

##### Flag

hackim19{dr_owl_thinks_you_are_smart}

##### Build
```sh
$ ./bin/ol -o hackim_challange_owl/dr-owl.c hackim_challange_owl/dr-owl.scm
$ gcc -o hackim_challange_owl/dr-owl hackim_challange_owl/dr-owl.c
```

#### Solution
breakpoint on xor condition for vm and collect all bytes xored with 0x4f
```sh
Breakpoint *0x407b48
pwndbg> set context-sections
pwndbg> commands
Type commands for breakpoint(s) 3, one per line.
End with a line saying just "end".
>telescope $rbp-0x88 1
>continue
>end
pwndbg> c
Continuing.
00:0000│   0x7fffffffdda8 ◂— 0x1a02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2702
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2e02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2c02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2402
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2602
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2202
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x7e02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x7602
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3402
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2b02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3d02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x1002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3802
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2302
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x1002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3b02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2702
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2602
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2102
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2402
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3c02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x1002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3602
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3a02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x1002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2e02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3d02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2a02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x1002
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3c02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2202
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x2e02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3d02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3b02
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x3202
Selected thread is running.
pwndbg> you gotta try harder
00:0000│   0x7fffffffdda8 ◂— 0x1902
Selected thread is running.
pwndbg> 00:0000│   0x7fffffffdda8 ◂— 0x1a02
Selected thread is running.
pwndbg>
Program received signal SIGTTOU, Stopped (tty output).
0x00007ffff7af9b40 in __tcsetattr (fd=0, optional_actions=<optimized out>, termios_p=0x617280 <tsettings>) at ../sysdeps/unix/sysv/linux/tcsetattr.c:83
83	../sysdeps/unix/sysv/linux/tcsetattr.c: No such file or directory.
Quit
Program received signal SIGTTOU
```
