#include "dicoloration.h"

int main(int argc, char *argv[])
{
    graph d[MAXN];
    int n;

    int stat[MAXN * MAXN];
    int i=0;
    for (i=0; i<MAXN*MAXN; i++) stat[i]=0;
    i = 0;
    int max_nb_a = 0;
    int nb_a;
    int nb = 0;
    while (1)
    {
      read_digraph6(stdin, d, &n);
      if (feof(stdin)) break;
      // print_graph(stderr, d, n);
      nb_a = number_of_arcs(d, n);
      ++nb;
      ++stat[nb_a];
      if (nb_a>max_nb_a) max_nb_a=nb_a;
    }
    
    for (i=0; i<max_nb_a && stat[i]==0; ++i); 
    for (; i<=max_nb_a; ++i)
    {
      printf("%d, %d \n", i, stat[i]);
    }
}

