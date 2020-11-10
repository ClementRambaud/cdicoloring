#include "dicoloration.h"

int main(int argc, char *argv[])
{
    char k = argv[1][0] - 48;
    graph d[MAXN];
    int n;
    while (1)
    {
      read_digraph6(stdin, d, &n);
      if (feof(stdin)) break;
      // print_graph(stderr, d, n);
      if (!is_kcol(d, n, k))
      {
        write_digraph6(stdout, d, n);
      }
    }
}

