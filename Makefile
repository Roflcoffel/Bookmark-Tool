default: vector.o option.o action.o color.o
	gcc -o bookmark main.c vector.o option.o action.o color.o

clean:
	rm -v *.o