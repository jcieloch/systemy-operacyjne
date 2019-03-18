FLAGS = -std=c99 -Wall

compile:
	gcc $(FLAGS) -o main main.c

clean:
	rm -f *.o
	rm -f *.txt
	rm -f main

generate:
	./main generate test.txt 10 20

sys_sort:
	./main sort test.txt 10 20 sys

lib_sort:
	./main sort test.txt 10 20 lib

sys_copy:
	./main copy test.txt test2.txt 8 20 sys

lib_copy:
	./main copy test.txt test2.txt 8 20 lib

all:
	make compile
	make test
	make clean

make test:
	./test.sh
