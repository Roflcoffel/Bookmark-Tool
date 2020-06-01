default: util vector file

file: vector.o util.o file.o color.o
	gcc -g -o file_tests file_test.c ../file.o ../vector.o ../util.o ../color.o

vector: vector.o util.o color.o
	gcc -g -o vector_tests vector_test.c ../vector.o ../util.o ../color.o

util: util.o color.o
	gcc -g -o util_tests util_test.c ../util.o ../color.o

file.o:
	gcc -c -o ../file.o ../file.c

vector.o:
	gcc -c -o ../vector.o ../vector.c

util.o:
	gcc -c -o ../util.o ../util.c

color.o:
	gcc -c -o ../color.o ../color.c

clean:
	rm -v ../*.o
