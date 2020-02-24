default: ../vector.o ../util.o
	gcc -o vector_tests vector_test.c ../vector.o
	gcc -o util_tests util_test.c ../util.o

vector: ../vector.o
	gcc -o vector_tests vector_test.c ../vector.o

util: ../util.o
	gcc -o util_tests util_test.c ../util.o

clean:
	rm -v ../*.o
