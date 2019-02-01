# Wonderwall

Flag: `w3Lc0m3_t0_tH3_8L4cK_p4R4D3`

Description: `Marty, we have to go back`

A simple re challenge written in OCaml.

This program just prints each character of the flag one by one. There are large delays between each successive print. The player has to figure out a way to print out the flag in a reasonable amount of time.

One solution is with function interposition using the `LD_PRELOAD` trick. We can run the program with ltrace and see which functions are called by the binary for introducing the delay and hook them accordingly.

```bash
(ctf) vagrant@amy:~/ctf/wond3rw4ll/dist$ ltrace ./wonderwall
...
gettimeofday(0x7ffd494ecb20, 0)                = 0
nanosleep(0x7ffd494ecb10, 0x7ffd494ecb10, 0, 0x556fa0cbd7b8) = 0
__errno_location()                             = 0x7f5b723d26c0
gettimeofday(0x7ffd494ecb20, 0)                = 0
write(1, "w", 1w)                               = 1
__errno_location()                             = 0x7f5b723d26c0
gettimeofday(0x7ffd494ecb00, 0)                = 0
nanosleep(0x7ffd494ecaf0, 0x7ffd494ecaf0, 0, 0x556fa0cbd7b8
...
```

We can hook `gettimeofday` and `nanosleep` to defeat the delay. Only overriding `nanosleep` isn't enough because the binary checks whether the defined delay amount has actually elapsed or not using `gettimeofday`.

Output:
```bash
(ctf) vagrant@amy:~/ctf/wond3rw4ll/solution$ make run
LD_PRELOAD=./time_machine.so ../dist/wonderwall
w3Lc0m3_t0_tH3_8L4cK_p4R4D3
```
