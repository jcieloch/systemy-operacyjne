FLAGS = -std=c99 -Wall

static:
	gcc $(FLAGS) -c library.c -o library.o
	ar rcs my_static_library.a library.o
	make clean

shared:
	gcc -fPIC $(FLAGS) -c library.c -o library.o
	gcc -fPIC $(FLAGS) -shared -o my_shared_library.so library.o
	make clean

clean:
	rm -f *.o
