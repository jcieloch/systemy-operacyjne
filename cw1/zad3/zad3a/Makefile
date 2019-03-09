FLAGS = -std=c99 -Wall

static:
	gcc $(FLAGS) -c library.c -o library.o
	ar rcs my_static_library.a library.o

	#linkowanie
	gcc $(FLAGS) main.c -I. my_static_library.a -o main_static

	make clean

shared:
	gcc -fPIC $(FLAGS) -c library.c -o library.o
	gcc -fPIC $(FLAGS) -shared -o my_shared_library.so library.o

	#linkowanie
	gcc $(FLAGS) -L. main.c -o main_shared my_shared_library.so

	make clean

dynamic:

	gcc -fPIC $(FLAGS) -c library.c -o library.o
	gcc -fPIC $(FLAGS) -shared -o my_dynamic_library.so library.o
	# linkowanie
	gcc $(FLAGS) -L. main.c -o main_dynamic -ldl -D DLL
	make clean

clean:
	rm -f *.o

test_all:
		make test_static
		#test_shared
		make test_dynamic

test_static:
	make static
	echo 'static' >> raport3a.txt
	echo './main_static create_table 4  search . main.c tmp_name remove_table' >> raport3a.txt
	./main_static create_table 4  search . main.c tmp_name remove_table
	echo './main_static create_table 4000000  search . main.c tmp_name remove_block 0 remove_table' >> raport3a.txt
	./main_static create_table 4000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_static create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table' >> raport3a.txt
	./main_static create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_static create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table' >> raport3a.txt
	./main_static create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table
	echo './main_static create_table 40000  search . main.c tmp_name remove_block 0 wartosc 10000 remove_table' >> raport3a.txt
	./main_static create_table 40000 search . main.c tmp_name remove_block 0 wartosc 10000 remove_table
	echo './main_static create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1 remove_table' >> raport3a.txt
	./main_static create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1 remove_table
	echo './main_static create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table' >> raport3a.txt
	./main_static create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table

test_shared:
	make shared
	echo 'shared' >> raport3a.txt
	echo './main_shared create_table 4  search . main.c tmp_name remove_table' >> raport3a.txt
	./main_shared create_table 4  search . main.c tmp_name remove_table
	echo './main_shared create_table 4000000  search . main.c tmp_name remove_block 0 remove_table' >> raport3a.txt
	./main_shared create_table 4000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_shared create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table' >> raport3a.txt
	./main_shared create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_shared create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table' >> raport3a.txt
	./main_shared create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table
	echo './main_shared create_table 40000  search . main.c tmp_name remove_block 0 wartosc 10000 remove_table' >> raport3a.txt
	./main_shared create_table 40000 search . main.c tmp_name remove_block 0 wartosc 10000 remove_table
	echo './main_shared create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1 remove_table' >> raport3a.txt
	./main_shared create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1 remove_table
	echo './main_shared create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table' >> raport3a.txt
	./main_shared create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table

test_dynamic:
	make dynamic
	echo 'dynamic' >> raport3a.txt
	echo './main_dynamic create_table 4  search . main.c tmp_name remove_table' >> raport3a.txt
	./main_dynamic create_table 4  search . main.c tmp_name remove_table
	echo './main_dynamic create_table 4000000  search . main.c tmp_name remove_block 0 remove_table' >> raport3a.txt
	./main_dynamic create_table 4000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_dynamic create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table' >> raport3a.txt
	./main_dynamic create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_dynamic create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table' >> raport3a.txt
	./main_dynamic create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table
	echo './main_dynamic create_table 40000  search . main.c tmp_name remove_block 0 wartosc 10000 remove_table' >> raport3a.txt
	./main_dynamic create_table 40000 search . main.c tmp_name remove_block 0 wartosc 10000 remove_table
	echo './main_dynamic create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1 remove_table' >> raport3a.txt
	./main_dynamic create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1 remove_table
	echo './main_dynamic create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table' >> raport3a.txt
	./main_dynamic create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table
