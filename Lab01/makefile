all: lib
	./main nguoidung.txt 20194663
lib: lib.o
	gcc -o main main.c acc.o dllist.o jval.o fields.o
lib.o:
	gcc -c lib/dllist.c lib/acc.c lib/jval.c lib/fields.c
clean: 
	rm -f lib/*.o *.o