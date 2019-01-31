__kernel void alpha(__global const float *A, __global float *B) {
    int i = get_global_id(0);
    B[i] = ((A[i] + 4.1) * 3.0) - 8.98;
    B[i] = ((B[i] + 1.03) * 1.998) - 3.201;
    B[i] = ((B[i] + 7.10345) * 5.0102) - 0.98912;
}
