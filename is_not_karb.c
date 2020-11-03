#include "dicoloration.h"

int main(int argc, char *argv[])
{
    char k = argv[1][0] - 48;
    graph g[MAXN * MAXN];
    int n;
    while (1)
    {
      read_graph6(stdin, g, &n);
      if (feof(stdin)) break;
      // print_graph(stderr, g, n);
      if (!is_karb(g, n, k))
      {
        write_graph6(stdout, g, n);
      }
    }
}

