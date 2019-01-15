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
