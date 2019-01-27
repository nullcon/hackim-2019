#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CL/cl.h>

#define MAX_SOURCE_SIZE 0x10000

char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
int alphabet_size = 63;

unsigned int index_of(char a) {
    for (int i = 0; i < alphabet_size; i++)
        if (a == alphabet[i])
            return i;
    exit(1);
}

int check_flag(char *s) {
    if  ((s[0] == 'i') && (s[1] == '7') && (s[2] == 'l') && (s[3] == 'x') && (s[4] == 'l') && (s[5] == 'M') && (s[6] == 'D') && (s[7] == 'x') && (s[8] == 'S') && (s[9] == 'i') && (s[10] == '4') && (s[11] == 'D') && (s[12] == 'l') && (s[13] == '_') && (s[14] == 'D') && (s[15] == 'G') && (s[16] == '1') && (s[17] == '_') && (s[18] == '_') && (s[19] == '1') && (s[20] == 'A'))
        return 0;
    return 1;
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
    int flag_size = 21;
    char input_str[100];
    int input_digit = 0;
    memset(input_str, 0, 100 * sizeof(char));
    printf("Enter input:\n");
    fgets(input_str, 99, stdin);
    
    int *A = (int*)malloc(sizeof(int) * flag_size);
    for (int i = 0; i < flag_size; i++)
        A[i] = index_of(input_str[i]);
    
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
    
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, flag_size * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, flag_size * sizeof(int), NULL, &ret);
    
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, flag_size * sizeof(int), A, 0, NULL, NULL);
    
    cl_program alpha = clCreateProgramWithBinary(context, 1, &device_id, &alpha_size, (const unsigned char**)&kernel_alpha, NULL, &ret);
    ret = clBuildProgram(alpha, 1, &device_id, NULL, NULL, NULL);
    cl_kernel alpha_bin = clCreateKernel(alpha, "alpha", &ret);
    
    ret = clSetKernelArg(alpha_bin, 0, sizeof(cl_mem), (void*)&a_mem_obj);
    ret = clSetKernelArg(alpha_bin, 1, sizeof(cl_mem), (void*)&b_mem_obj);
    
    size_t global_item_size = flag_size;
    ret = clEnqueueNDRangeKernel(command_queue, alpha_bin, 1, NULL, &global_item_size, NULL, 0, NULL, NULL);
    
    int *B = (int*)malloc(sizeof(int) * flag_size);
    ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, flag_size * sizeof(int), B, 0, NULL, NULL);
    
    char *C = (char*)malloc(sizeof(char) * flag_size + 1);
    for (int i = 0; i < flag_size; i++)
        C[i] = alphabet[B[i] % alphabet_size];
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
    
    if (success == 0)
        return 0;
    else
        return 1;
}
