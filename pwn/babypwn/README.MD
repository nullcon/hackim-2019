# name:babypwn
description: Can you exploit the basic bugs?

# flag: hackim19{h0w_d1d_y0u_g37_th4t_c00k13?!!?}

# solution
- Exploit integer overflow to get buffer overflow
- Bypass stack canary by passing '+'/'-' in `scanf` when overwriting canary
- Leak addresses using format string
- Rerun main function using bof
- craft rop to system