FLAGS = -std=c99 -std=gnu99 -Wall

compile:
	gcc $(FLAGS) -o main main.c

test:
	./main '/home/kuba/sysopy/cw02' '>' '2019-03-18 20:40:00' 'nftw'
	./main '/home/kuba/sysopy/cw02' '>' '2019-03-18 20:40:00'

clean:
	rm -f *.o
	rm -f *.txt
	rm -f main
