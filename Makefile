all: is_kcritical is_not_kcol
is_kcritical: is_kcritical.c dicoloration.c dicoloration.h
	gcc -Wall -O4 -o is_kcritical.native is_kcritical.c dicoloration.c
is_not_kcol: is_not_kcol.c dicoloration.c dicoloration.h
	gcc -Wall -O4 -o is_not_kcol.native is_not_kcol.c dicoloration.c



