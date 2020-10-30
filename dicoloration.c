#include <stdio.h>

#define MAXN 32

typedef int set; /* binary representation */
typedef set graph; /* graph are array of int */
typedef int bool;
#define TRUE 1
#define FALSE 0

#define EMPTY 0
#define ALL (~EMPTY)
#define UNION(a,b) a | b
#define INTERSECT(a,b) a & b
#define DIFF(a,b) a & (~b)
#define SINGLETON(x) (1 << x)
#define ISEMPTY(a) ((a)==EMPTY)
#define IN(x,a) (!ISEMPTY(INTERSECT(a, SINGLETON(x))))
#define ADD(x, a) UNION(a, SINGLETON(x))

#define ADJ_SET(g, v) (g[v]) 
#define IS_ADJ(g,u,v) IN(v, ADJ_SET(g, u))

#define CEILING(p,q) (1 + ((p-1)/q))

void add_edge(graph* g, int u, int v)
{
  // fprintf(stderr, "add_edge(g, %d, %d) \n", u, v); 
  ADJ_SET(g,u) = ADD(v, ADJ_SET(g,u));
}

void empty_graph(graph* g, int n)
{
  int i;
  for (i=0; i<n; ++i)
  {
    g[i] = EMPTY;
  }
}

void read_digraph6(FILE *fi, graph* d, int *n)
/* fi: file;
 * n: the number of vertices will be written here;
 */
{
  char c; /* current character */
  int i,j; /* the current pair of vertices */
  int nb;
  int index;
  int matij;
  char line[MAXN*MAXN]; /* it is indeed smaller  <------------ */


  c = fgetc(fi);
  if (c!='&') /* if it is not a directed graph */
  {
    return;
  }

  *n = fgetc(fi) - 63;
  /* we read the line */
  c = fgetc(fi);
  int counter=0;
  while (c!='\n')
  {
    line[counter] = c;
    c = fgetc(fi);
    ++counter;
  }

  for (j=0; j<*n; ++j)
  {
    for (i=0; i<*n; ++i)
    {
      nb = (*n) * j + i;
      index = nb % 6;
      c = line[nb/6] - 63;
      matij = (c >> (5-index)) & 1;
      if (matij==1)
      {
        // fprintf(stderr, "is_adj %d %d \n", i ,j);
        add_edge(d, i, j);
      }
    }
  }
}

void print_graph(FILE* fi, graph* g, int n)
{
  int i,j;
  fprintf(fi, "graph of order %d: \n", n);
  for (i=0; i<n; ++i)
  {
    fprintf(fi, "%d: ", i);
    for (j=0; j<n; ++j)
    {
      if IS_ADJ(g, i, j)
      {
        fprintf(fi, "%d ", j);
      }
    }
    fprintf(fi, "\n");
  }
  fprintf(fi, "\n");
}

void write_digraph6(FILE* fi, graph* d, int n)
{
  int taille = CEILING(n*n, 6); /* nb of needed char */
  char result[CEILING(MAXN*MAXN, 6)];
  int i,j;
  int v;
  int nb, index_char, index;

  /* clear the result */
  for (i=0; i<taille; ++i)
  {
    result[i] = 0;
  }

  for (i=0; i<n; ++i)
  {
    for (j=0; j<n; ++j)
    {
      if (IS_ADJ(d, j, i))
      {
        // fprintf(stderr, "is_adj %d %d \n", i, j);
        v = 1;
      }
      else
      {
        v = 0;
      }
      nb = i * n + j;
      index_char = nb / 6;
      index = nb % 6;
      // fprintf(stderr, "index = %d, index_char = %d, (v << (5-index)) = %d \n",
      //         index, index_char, (v << (5 - index)));
      result[index_char] |= (v << (5 - index));
      // fprintf(stderr, "%x\n", result[index_char]);
    }
  }
  fputc('&', fi); /* directed */
  fputc(63 + n, fi); /* nb of vertices */
  for (i=0; i<taille; ++i)
  {
    fputc(result[i] + 63, fi);
  }
  fputc('\n', fi);
}

#define NONVISITED 0
#define VISITED    1
#define INPROGRESS 2
bool has_cycle_mask(graph* g, int n, set mask)
{
  int u,v,w;

  bool state[n];
  /* clear states */
  int i;
  for (i=0; i<n; ++i)
  {
    state[i] = NONVISITED;
  }
  
  int stack[n];
  int top = -1; /* top of the stack */

  /* we put all vertices on the stack */
  for (v=0; v<n; ++v)
  {
    ++top;
    stack[top] = v;
  }

  set gv; /* current list of successors */

  for (u=0; u<n; ++u)
  {
    if (state[u]!=NONVISITED)
    {
      break;
    }

    /* we push u */
    ++top;
    stack[top] = u;

    while (top>=0) /* while the stack is not empty */
    {
      v = stack[top]; /* we process the vertex on the top */
      --top;
      
      gv = ADJ_SET(g, v);
      for (w=0; w<n; ++w)
      {
        if (IN(gv, w)) /* if w is a successor of v */
        {
          switch (state[w])
          {
            case INPROGRESS: /* we have any cycle */
              return TRUE;
              break;
            
            case VISITED: /* we don't need to go further */
              break;

            case NONVISITED: /* we push w on the stack */
              ++top;
              stack[top] = w;
              state[w] = INPROGRESS;
              fprintf(stderr, "we push %d \n", w);
              break;
          }
        }
      }
      state[v] = VISITED;
    }
  }
  return FALSE;
}

bool has_cycle(graph* g, int n)
{
  return has_cycle_mask(g, n, ALL);
}


int main()
{
    graph d[MAXN * MAXN];
    int n;
    while (1)
    {
      empty_graph(d, MAXN); /* clear the graph */
      read_digraph6(stdin, d, &n);
      if (feof(stdin)) break;
      // print_graph(stderr, d, n);
      if (!has_cycle(d, n))
      {
        write_digraph6(stdout, d, n);
      }
    }
}




