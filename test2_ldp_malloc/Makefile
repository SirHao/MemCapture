all: mem.c
	gcc -c -g -O3 -Wall -fPIC mem.c
	gcc -g -shared -o Mem.so mem.o  -ldl

clean:
	rm -f *.so *.o