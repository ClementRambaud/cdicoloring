all: 
	gcc -Wall -march=native -Ofast -o is_kcritical.native is_kcritical.c dicoloration.c
	gcc -Wall -march=native -Ofast -o is_not_kcol.native is_not_kcol.c dicoloration.c

clean:
	rm *.native



