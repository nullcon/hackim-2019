# c0mpute
Flag: `nv1d14_d03S_1t_8etteR`

OpenCL re chal

The program takes input from user and runs an OpenCL kernel on that input. It then compares character by character the string after the transformation to check whether the input provided by the user is satisfactory.

The transformation done is extremely trivial. We have a global alphabet array which stores `a-zA-Z0-9_`. Indices into this alphabet array are calculated from the user input. This array of indices then undergoes the simple transformation:

```c
B[i] = ((A[i] + 4) * 3) - 9; // A is the input index int array
B[i] = ((B[i] + 1) * 2) - 3;
B[i] = ((B[i] + 7) * 5) - 1;
```

This kernel is opimised by the Intel OpenCL compiler to:
```c
B[i] = 30 * A[i] + 52
```

This new array of indices `B` is used to calculate the string post transformation from the alphabet array. All indices are `idx % len(alphabet)`.

Then a function compares this new string character by character for validation.

The OpenCL kernel can be reversed by dumping the `.ocl.obj` section of the kernel and disassembling it. The script to do so is present in the `solution` folder.
