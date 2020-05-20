default: vector util

vector: vector.o
	gcc -g -o vector_tests vector_test.c ../vector.o

util: util.o
	gcc -g -o util_tests util_test.c ../util.o

vector.o:
	gcc -c -o ../vector.o ../vector.c

util.o:
	gcc -c -o ../util.o ../util.c

clean:
	rm -v ../*.o
