all:
	g++ -fPIC -c -o time_machine.o time_machine.cpp
	g++ -fPIC -shared -o time_machine.so time_machine.o
run:
	LD_PRELOAD=./time_machine.so ../dist/wonderwall
