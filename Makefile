INSTALL_PATH:=$(if $(INSTALL_PATH),$(INSTALL_PATH),"~/Program/Bookmark")

default: vector.o util.o file.o command.o action.o color.o
	gcc -g -o bookmark main.c vector.o util.o file.o command.o action.o color.o 

clean:
	rm -v *.o

install: default
	mkdir -p $(INSTALL_PATH)
	cp bookmark $(INSTALL_PATH)
	ln -s -f -t ~/bin $(INSTALL_PATH)/bookmark