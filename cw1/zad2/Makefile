FLAGS = -std=c99 -Wall

static:
	gcc $(FLAGS) -c library.c -o library.o
	ar rcs my_static_library.a library.o

	#linkowanie
	gcc $(FLAGS) main.c -I. my_static_library.a -o main_static

	make clean

clean:
	rm -f *.o

test_static:
	make static
	echo 'static' >> raport2.txt
	echo './main_static create_table 4  search . main.c tmp_name remove_table' >> raport2.txt
	./main_static create_table 4  search . main.c tmp_name remove_table
	echo './main_static create_table 4000000  search . main.c tmp_name remove_block 0 remove_table' >> raport2.txt
	./main_static create_table 4000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_static create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table' >> raport2.txt
	./main_static create_table 40000000000  search . main.c tmp_name remove_block 0 remove_table
	echo './main_static create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table' >> raport2.txt
	./main_static create_table 40000  search . main.c tmp_name remove_block 0 wartosc 100 remove_table
	echo './main_static create_table 40000  search . main.c tmp_name remove_block 0 wartosc 10000 remove_table' >> raport2.txt
	./main_static create_table 40000 search . main.c tmp_name remove_block 0 wartosc 10000 remove_table
	echo './main_static create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1 remove_table' >> raport2.txt
	./main_static create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1 remove_table
	echo './main_static create_table 40000  search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table' >> raport2.txt
	./main_static create_table 40000 search . *.txt tmp_name remove_block 0 wartosc 1000 remove_table
