# c0mpute
Flag: `nv1d14_d03S_1t_8etteR`

OpenCL re chal

The program takes input from user and runs an OpenCL kernel on that input. It then compares character by character the string after the transformation to check whether the input provided by the user is satisfactory.

The transformation done is extremely trivial. We have a global alphabet array which stores `a-zA-Z0-9_`. Indices into this alphabet array are calculated from the user input. This array of indices then undergoes the simple transformation:

```c
B[i] = ((A[i] + 4.1) * 3.0) - 8.98;             // A is input alphabet index int array
B[i] = ((B[i] + 1.03) * 1.998) - 3.201;
B[i] = ((B[i] + 7.10345) * 5.0102) - 0.98912;
```

This new array of indices `B` is used to calculate the string post transformation from the alphabet array. All indices are `idx % len(alphabet)`.

Then a function compares this new string character by character for validation.

The OpenCL kernel can be reversed by dumping the `.ocl.obj` section of the kernel and disassembling it. The script to do so is present in the `solution` folder along with the ocl obj for the kernel used.
