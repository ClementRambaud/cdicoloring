all: 
	gcc -Wall -O4 -o is_kcritical.native is_kcritical.c dicoloration.c
	gcc -Wall -O4 -o is_not_kcol.native is_not_kcol.c dicoloration.c



