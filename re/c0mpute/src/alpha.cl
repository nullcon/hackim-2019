__kernel void alpha(__global const int *A, __global int *B) {
    int i = get_global_id(0);
    B[i] = ((A[i] + 4) * 3) - 9;
    B[i] = ((B[i] + 1) * 2) - 3;
    B[i] = ((B[i] + 7) * 5) - 1;
}
