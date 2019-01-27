all:
	gcc -o compute main.c -l OpenCL -O1
	mkdir -p obj
	ioc64 -cmd=build -input=alpha.cl -device=cpu -simd=avx2 -ir=obj/alpha.bin
