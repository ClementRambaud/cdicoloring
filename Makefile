all: dicoloration directg

directg: nauty/nauty.a directg_deg_min_2.c directg_deg_min_3.c
	gcc -march=native -O4 -o directg_deg_min_2.native directg_deg_min_2.c nauty/nauty.a
	gcc -march=native -O4 -o directg_deg_min_3.native directg_deg_min_3.c nauty/nauty.a

nauty/nauty.a:
	wget http://pallini.di.uniroma1.it/nauty27r1.tar.gz
	tar xvf nauty27r1.tar.gz
	mv nauty27r1 nauty
	make -C nauty/ nauty.a

dicoloration: dicoloration.o is_kcritical.c is_not_kcol.c is_not_kcol.c
	gcc -Wall -march=native -Ofast -o is_kcritical.native is_kcritical.c dicoloration.o
	gcc -Wall -march=native -Ofast -o is_not_kcol.native is_not_kcol.c dicoloration.o
	gcc -Wall -march=native -Ofast -o is_not_karb.native is_not_karb.c dicoloration.o
	gcc -Wall -march=native -Ofast -o density_statistics.native density_statistics.c dicoloration.o

dicoloration.o: dicoloration.c dicoloration.h
	gcc -Wall -march=native -Ofast -c dicoloration.c

clean:
	rm *.native
	rm *.o
	rm *.tar.gz
	rm -r nauty



