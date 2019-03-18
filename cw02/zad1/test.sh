#!/bin/bash

rm -f wyniki.txt
rm -f test.txt
rm -f test2.txt
for i in 1 4 512 1024 4096 8192
do
  echo $i
	echo "./main generate test.txt 1000 $i" >> wyniki.txt
	./main generate test.txt 1000 $i
	echo "./main copy test.txt test2.txt 1000 $i lib" >> wyniki.txt
	./main copy test.txt test2.txt 1000 $i lib
	echo "./main sort test2.txt 1000 $i lib" >> wyniki.txt
	./main sort test2.txt 1000 $i lib
	rm -f test2.txt
	echo "./main copy test.txt test2.txt 1000 $i sys" >> wyniki.txt
	./main copy test.txt test2.txt 1000 $i sys
	echo "./main sort test2.txt 1000 $i sys" >> wyniki.txt
	./main sort test2.txt 1000 $i sys
	rm -f test.txt
	rm -f test2.txt
	echo "./main generate test.txt 10000 $i" >> wyniki.txt
	./main generate test.txt 10000 $i
	echo "./main copy test.txt test2.txt 10000 $i lib" >> wyniki.txt
	./main copy test.txt test2.txt 10000 $i lib
	echo "./main sort test2.txt 10000 $i lib" >> wyniki.txt
	./main sort test2.txt 10000 $i lib
	rm -f test2.txt
	echo "./main copy test.txt test2.txt 10000 $i sys" >> wyniki.txt
	./main copy test.txt test2.txt 10000 $i sys
	echo "./main sort test2.txt 10000 $i sys" >> wyniki.txt
	./main sort test2.txt 10000 $i sys
	rm -f test.txt
	rm -f test2.txt
done
