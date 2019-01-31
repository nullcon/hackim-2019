#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CL/cl.h>

#define MAX_SOURCE_SIZE 0x10000

char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
int alphabet_size = 63;
int flag_size = 21;

unsigned int index_of(char a) {
    for (int i = 0; i < alphabet_size; i++)
        if (a == alphabet[i])
            return i;
    exit(1);
}

int check_flag(char *s) {
    //l _ p A p Q I A W m 8 I p c I K 4 c c 4 E
    int solve[21];
    for (int i = 0; i < flag_size; i++)
        solve[i] = 0;

    if (s[0] == 'l')
        solve[0] = 1;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[1] == '_')
        solve[1] = 2;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[2] == 'p')
        solve[2] = 3;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[3] == 'A')
        solve[3] = 4;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[4] == 'p')
        solve[4] = 5;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[5] == 'Q')
        solve[5] = 6;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[6] == 'I')
        solve[6] = 7;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[7] == 'A')
        solve[7] = 8;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[8] == 'W')
        solve[8] = 9;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[9] == 'm')
        solve[9] = 10;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[10] == '8')
        solve[10] = 11;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[11] == 'I')
        solve[11] = 12;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[12] == 'p')
        solve[12] = 13;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[13] == 'c')
        solve[13] = 14;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[14] == 'I')
        solve[14] = 15;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[15] == 'K')
        solve[15] = 16;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[16] == '4')
        solve[16] = 17;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[17] == 'c')
        solve[17] = 18;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[18] == 'c')
        solve[18] = 19;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[19] == '4')
        solve[19] = 20;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    if (s[20] == 'E')
        solve[20] = 21;
    else
        __asm__(
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
            "nop;"
        );
    int sum = 0;
    for (int i = 0; i < flag_size; i++)
        sum += solve[i];
    return (sum == ((flag_size * (flag_size + 1)) / 2));
}

int read_kernel(const char *kernel_name, char *kernel_buf) {
     size_t kernel_source_size = 0;
     FILE *fp = fopen(kernel_name, "rb");
     if (!fp) {
         printf("Failed to open kernel\n");
         exit(1);
     }
     kernel_source_size = fread(kernel_buf, 1, MAX_SOURCE_SIZE, fp);
     fclose(fp);

     return kernel_source_size;
}

int main(void) {
    char input_str[100];
    int input_digit = 0;
    memset(input_str, 0, 100 * sizeof(char));
    printf("Enter input:\n");
    fgets(input_str, 99, stdin);
    
    float *A = (float*)malloc(sizeof(float) * flag_size);
    for (int i = 0; i < flag_size; i++)
        A[i] = (float)index_of(input_str[i]);
    
    char *kernel_alpha = (char*)malloc(MAX_SOURCE_SIZE);
    size_t alpha_size = read_kernel("obj/alpha.bin", kernel_alpha);

    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices = 0;
    cl_uint ret_num_platforms = 0;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, flag_size * sizeof(float), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, flag_size * sizeof(float), NULL, &ret);
    
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, flag_size * sizeof(float), A, 0, NULL, NULL);
    
    cl_program alpha = clCreateProgramWithBinary(context, 1, &device_id, &alpha_size, (const unsigned char**)&kernel_alpha, NULL, &ret);
    ret = clBuildProgram(alpha, 1, &device_id, NULL, NULL, NULL);
    cl_kernel alpha_bin = clCreateKernel(alpha, "alpha", &ret);
    
    ret = clSetKernelArg(alpha_bin, 0, sizeof(cl_mem), (void*)&a_mem_obj);
    ret = clSetKernelArg(alpha_bin, 1, sizeof(cl_mem), (void*)&b_mem_obj);
    
    size_t global_item_size = flag_size;
    ret = clEnqueueNDRangeKernel(command_queue, alpha_bin, 1, NULL, &global_item_size, NULL, 0, NULL, NULL);
    
    float *B = (float*)malloc(sizeof(float) * flag_size);
    ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, flag_size * sizeof(float), B, 0, NULL, NULL);
    
    char *C = (char*)malloc(sizeof(char) * flag_size + 1);
    int temp = 0;
    for (int i = 0; i < flag_size; i++) {
        temp = (int)B[i];
        C[i] = alphabet[temp % alphabet_size];
    }
    C[flag_size] = '\0';
    
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(alpha_bin);
    ret = clReleaseProgram(alpha);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    
    free(A);
    free(B);

    int success = check_flag(C);
    free(C);
    
    if (success)
        return 0;
    else
        return 1;
}
