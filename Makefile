default: vector.o command.o action.o color.o
	gcc -g -o bookmark main.c vector.o command.o action.o color.o 

clean:
	rm -v *.o