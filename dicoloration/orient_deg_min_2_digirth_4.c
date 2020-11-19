#include "dicoloration.h"

void orient(FILE *file, graph *g, graph *d, int n, int v)
{
  if (v >= n)
  {
    write_digraph6(file, d, n);
    return;
  }

  int w = MIN_SET(g[v]);

  if (w > n)
  {
    if (deg_out(d, n, v)>=2 && deg_in(d, n, v) >= 2)
    {
      orient(file, g, d, n , v+1);
    }
    return;
  }

  /* remove edge vw */
  g[v] &= ~SINGLETON(w);
  g[w] &= ~SINGLETON(v);

  int u;
  int dw, dv;
  bool can_add;
  /* add arc vw */
  dw = d[w];
  can_add = TRUE;
  while ((u=MIN_SET(dw))<n)
  {
    dw &= ~SINGLETON(u);
    if (IS_ADJ(d, u, v))
    {
      can_add = FALSE;
      break;
    }
  }
  if (can_add)
  {
    d[v] |=  SINGLETON(w);
    orient(file, g, d, n, v);
    d[v] &= ~SINGLETON(w);
  }

  /* add arc wv */
  can_add = TRUE;
  dv = d[v];
  while ((u=MIN_SET(dv))<n)
  {
    dv &= ~SINGLETON(u);
    if (IS_ADJ(d, u, w))
    {
      can_add = FALSE;
      break;
    }
  }
  if (can_add)
  d[w] |=  SINGLETON(v);
  orient(file, g, d, n, v);
  d[w] &= ~SINGLETON(v);

  /* readd edge v w */
  g[v] |= SINGLETON(w);
  g[w] |= SINGLETON(v);
}


int main(int argc, char *argv[])
{
  graph g[MAXN];
  graph d[MAXN];
  int n;
  while (1)
  {
    read_graph6(stdin, g, &n);
    if (feof(stdin)) break;
    empty_graph(d, n);
    orient(stdout, g, d, n, 0);
  }
}




