all: dicoloration_all my_directg directg geng

my_directg: directg_deg_min_2.native directg_deg_min_3.native
directg_deg_min_2.native: nauty/nauty.a directg_modified/directg_deg_min_2.c
	gcc -march=native -O4 -o directg_deg_min_2.native directg_modified/directg_deg_min_2.c nauty/nauty.a
directg_deg_min_3.native: nauty/nauty.a directg_modified/directg_deg_min_3.c
	gcc -march=native -O4 -o directg_deg_min_3.native directg_modified/directg_deg_min_3.c nauty/nauty.a

directg:
	make -C nauty/ directg

geng:
	make -C nauty/ geng


nauty/nauty.a:
	wget http://pallini.di.uniroma1.it/nauty27r1.tar.gz
	tar xvf nauty27r1.tar.gz
	mv nauty27r1 nauty
	make -C nauty/ nauty.a

dicoloration_all: is_kcritical.native is_not_kcol.native is_not_karb.native density_statistics.native digirth_at_leastk.native cant_be_part_in_k_chordals.native orient_deg_min_2_digirth_4.native

is_kcritical.native: dicoloration.o dicoloration/is_kcritical.c
	gcc -Wall -march=native -Ofast -o is_kcritical.native dicoloration/is_kcritical.c dicoloration.o

orient_deg_min_2_digirth_4.native: dicoloration.o dicoloration/orient_deg_min_2_digirth_4.c
	gcc -Wall -march=native -Ofast -o orient_deg_min_2_digirth_4.native dicoloration/orient_deg_min_2_digirth_4.c dicoloration.o

is_not_kcol.native: dicoloration.o dicoloration/is_not_kcol.c
	gcc -Wall -march=native -Ofast -o is_not_kcol.native dicoloration/is_not_kcol.c dicoloration.o

is_not_karb.native: dicoloration.o dicoloration/is_not_karb.c
	gcc -Wall -march=native -Ofast -o is_not_karb.native dicoloration/is_not_karb.c dicoloration.o

cant_be_part_in_k_chordals.native: dicoloration.o dicoloration/cant_be_part_in_k_chordals.c
	gcc -Wall -march=native -Ofast -o cant_be_part_in_k_chordals.native dicoloration/cant_be_part_in_k_chordals.c dicoloration.o

digirth_at_leastk.native: dicoloration.o dicoloration/digirth_at_leastk.c
	gcc -Wall -march=native -Ofast -o digirth_at_leastk.native dicoloration/digirth_at_leastk.c dicoloration.o

density_statistics.native: dicoloration.o dicoloration/density_statistics.c
	gcc -Wall -march=native -Ofast -o density_statistics.native dicoloration/density_statistics.c dicoloration.o

dicoloration.o: dicoloration/dicoloration.c dicoloration/dicoloration.h
	gcc -Wall -march=native -Ofast -c dicoloration/dicoloration.c

clean:
	rm *.native
	rm *.o
	rm *.tar.gz
	rm -r nauty



