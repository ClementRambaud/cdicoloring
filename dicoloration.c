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

int deg_out(graph* g, int n, int v)
{
  set gv = ADJ_SET(g, v);
  int res = 0;
  int w;
  for (w=0; w<n; ++w)
  {
    if (IN(w, gv)) ++res;
  }
  return res;
}

int deg_in(graph* g, int n, int v)
{
  int res = 0;
  int w;
  for (w=0; w<n; ++w)
  {
    if (IS_ADJ(g, w, v)) ++res;
  }
  return res;
}

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
int deg_out_min(graph* g, int n)
{
  int res = 1<<30;
  int v;
  for (v=0; v<n; ++v)
  {
    res = MIN(res, deg_in(g,n,v));
  }
  return res;
}

int deg_in_min(graph* g, int n)
{
  int res = 1<<30;
  int v;
  for (v=0; v<n; ++v)
  {
    res = MIN(res, deg_out(g,n,v));
  }
  return res;
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

  empty_graph(d, MAXN); /* clear the graph */

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
        add_edge(d, j, i);
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
      if (IS_ADJ(d, i, j))
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
  // fprintf(stderr, "is_acyclic? n = %d; mask = %x \n", n, mask);

  bool state[n];
  /* clear states */
  for (u=0; u<n; ++u)
  {
    state[u] = NONVISITED;
    // fprintf(stderr, "IN(%d, mask)? %d \n", u, IN(u, mask));
  }
 
  int stack[n];
  int top = -1; /* top of the stack */

  set gv; /* current list of successors */
 
  bool process_finished;

  for (u=0; u<n; ++u)
  {
    // fprintf(stderr, "IN(%d, %x)? %d \n", u, mask, IN(u, mask));
    if ((state[u]!=NONVISITED) || (!IN(u, mask)))
    {
      continue;
    }

    /* we push u */
    ++top;
    stack[top] = u;
    state[u] = INPROGRESS;
    // fprintf(stderr, "--> we push %d \n", u);

    while (top>=0) /* while the stack is not empty */
    {
      v = stack[top]; /* we process the vertex on the top */
      state[v] = INPROGRESS;
      // fprintf(stderr, "we pop %d \n", v);
 
      process_finished = TRUE;
      gv = ADJ_SET(g, v);
      for (w=0; w<n; ++w)
      {
        // fprintf(stderr, "we try (v, w) = (%d , %d) \n", v, w);
        if (IN(w, gv) && IN(w, mask)) /* if w is a successor of v in mask */
        {
          // fprintf(stderr, "-------------> TRUE, w= %d, state[w]=%d \n", w, state[w]);
          switch (state[w])
          {
            case INPROGRESS: /* we have any cycle */
              // fprintf(stderr, "cycle found at %d \n", w);
              return TRUE;
              break;
 
            case VISITED: /* we don't need to go further */
              break;

            case NONVISITED: /* we push w on the stack */
              ++top;
              stack[top] = w;
              process_finished = FALSE;
              // fprintf(stderr, "we push %d \n", w);
              break;
          }
        }
      }
      if (process_finished)
      {
        --top;
        state[v] = VISITED;
      }
    }
  }
  return FALSE;
}

bool has_cycle(graph* g, int n)
{
  return has_cycle_mask(g, n, ALL);
}


bool is_kcol_aux(graph* d, int n, int k, set current_subgraph, set current_acyclic,
                 int next_vertex)
 /* next_vertex: next vertex to add to acyclic */
{
  // fprintf(stderr, "n = %d, next_vertex = %d, k = %d,subg = %x, acyclic = %x \n", n,
  //         next_vertex, k,
  //         current_subgraph, current_acyclic);
  if (k==0)
  {
    return (n==0);
  }

  if (k==1)
  {
    return !has_cycle_mask(d, n, current_subgraph);
  }
  
  if (next_vertex >= n)
  {
    // fprintf(stderr, "final acyclic = %x \n", current_acyclic);
    return is_kcol_aux(d, n, k - 1, DIFF(current_subgraph, current_acyclic), EMPTY, 0);
  }

  /* if we can not add next_vertex */
  if (!IN(next_vertex, current_subgraph) ||
      has_cycle_mask(d, n, ADD(next_vertex,current_acyclic)))
  {
    return is_kcol_aux(d, n, k, current_subgraph, current_acyclic, next_vertex + 1);
  }

  /* if we can add the vertex */
  return (is_kcol_aux(d, n, k, current_subgraph, 
                      ADD(next_vertex, current_acyclic), next_vertex + 1) ||
          is_kcol_aux(d, n, k, current_subgraph, current_acyclic, next_vertex + 1));
}


bool is_kcol(graph* d, int n, int k)
{
  return is_kcol_aux(d, n, k, ALL, EMPTY, 0); 
}

bool is_kvertex_critical(graph* d, int n, int k)
{
  if (is_kcol(d, n, k-1) || !is_kcol(d, n, k))
  {
    return FALSE;
  }
  int v;
  for (v=0; v<n; ++v)
  {
    if (!is_kcol_aux(d, n, k-1, DIFF(ALL, SINGLETON(v)), EMPTY, 0))
    {
      return FALSE;
    }
  }
  return TRUE;
}


int main()
{
    graph d[MAXN * MAXN];
    int n;
    const int k = 3;
    while (1)
    {
      read_digraph6(stdin, d, &n);
      if (feof(stdin)) break;
      // print_graph(stderr, d, n);
      if ((deg_out_min(d,n) >= k-1) && (deg_in_min(d,n) >= k-1) &&
          is_kvertex_critical(d, n, k))
      {
        write_digraph6(stdout, d, n);
      }
    }
}




