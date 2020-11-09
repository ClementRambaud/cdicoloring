all: dicoloration.o
	gcc -Wall -march=native -Ofast -o is_kcritical.native is_kcritical.c dicoloration.o
	gcc -Wall -march=native -Ofast -o is_not_kcol.native is_not_kcol.c dicoloration.o
	gcc -Wall -march=native -Ofast -o is_not_karb.native is_not_karb.c dicoloration.o

dicoloration.o:
	gcc -Wall -march=native -Ofast -c dicoloration.c

clean:
	rm *.native
	rm *.o



