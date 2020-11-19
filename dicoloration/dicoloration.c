#include "dicoloration.h" 

inline void add_edge(graph* g, int u, int v)
{
  ADJ_SET(g,u) = ADD(v, ADJ_SET(g,u));
}

inline void remove_edge(graph* g, int u, int v)
{
  ADJ_SET(g,u) = DEL(v, ADJ_SET(g,u));
}

inline void empty_graph(graph* g, int n)
{
  int i;
  for (i=0; i<n; ++i)
  {
    g[i] = EMPTY;
  }
}

inline void copy_graph(graph* g, graph* g2, int n)
{
  int v;
  for(v=0; v<n; ++v)
  {
    ADJ_SET(g2, v) = ADJ_SET(g, v);
  }
}

inline int deg_out(graph* g, int n, int v)
{
  return CARD(ADJ_SET(g, v));
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

inline int deg_min(graph* g, int n)
{
  return deg_out_min(g, n);
}

inline int number_of_arcs(graph* d, int n)
{
  int res = 0;
  int v;
  for (v=0; v<n; ++v)
  {
    res += CARD(ADJ_SET(d, v));
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

  empty_graph(d, MAXN); /* clear the graph */

  c = fgetc(fi);
  if (c != '&') /* if it is not a directed graph */
  {
    return;
  }

  *n = fgetc(fi) - 63; /* we get the  numbe rof vertices */

  /* we read the matrix */
  nb = 0;
  for (i=0; i<*n; ++i)
  {
    for (j=0; j<*n; ++j)
    {
      // nb = (*n) * i + j;
      index = nb % 6;
      if (index == 0) /* we need another character */
      {
        c = fgetc(fi) - 63;
      }
      matij = (c >> (5-index)) & 1;
      if (matij)
      {
        // fprintf(stderr, "is_adj %d %d \n", i ,j);
        add_edge(d, i, j);
      }
      ++nb;
    }
  }
  if (fgetc(fi) != '\n' && fgetc(fi) != EOF)
  {
    fprintf(stderr, "ATTENTION, mauvaise lecture! \n");
  }
}

void read_graph6(FILE *fi, graph* g, int *n)
/* fi: file;
 * n: the number of vertices will be written here;
 */
{
  char c=0; /* current character */
  int i,j; /* the current pair of vertices */
  int nb;
  int index;
  int matij;

  empty_graph(g, MAXN); /* clear the graph */

  *n = fgetc(fi) - 63; /* we get the  numbe rof vertices */

  /* we read the matrix */
  nb = 0;
  for (i=0; i<*n; ++i)
  {
    for (j=0; j<i; ++j)
    {
      // nb = (*n) * i + j;
      index = nb % 6;
      if (index == 0) /* we need another character */
      {
        c = fgetc(fi) - 63;
      }
      matij = (c >> (5-index)) & 1;
      if (matij)
      {
        // fprintf(stderr, "is_adj %d %d \n", i ,j);
        add_edge(g, i, j);
        add_edge(g, j, i);
      }
      ++nb;
    }
  }
  if (fgetc(fi) != '\n' && fgetc(fi) != EOF)
  {
    fprintf(stderr, "ATTENTION, mauvaise lecture! \n");
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

  nb = 0;
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
      index_char = nb / 6;
      index = nb % 6;
      // fprintf(stderr, "index = %d, index_char = %d, (v << (5-index)) = %d \n",
      //         index, index_char, (v << (5 - index)));
      result[index_char] |= (v << (5 - index));
      // fprintf(stderr, "%x\n", result[index_char]);
      ++nb;
    }
  }
  fputc('&', fi); /* directed */
  fputc(63 + n, fi); /* nb of vertices */
  for (i=0; i<taille; ++i)
  { /* then we print the adj matrix */
    fputc(result[i] + 63, fi);
  }
  fputc('\n', fi);
}
void write_graph6(FILE* fi, graph* d, int n)
{
  int taille = CEILING(n*(n-1), 12); /* nb of needed char */
  // fprintf(stderr, "taille = %d \n", taille);
  char result[CEILING(MAXN*MAXN, 6)];
  int i,j;
  int v;
  int nb, index_char, index;

  /* clear the result */
  for (i=0; i<taille; ++i)
  {
    result[i] = 0;
  }

  nb = 0;
  for (i=0; i<n; ++i)
  {
    for (j=0; j<i; ++j)
    {
      if (IS_ADJ(d, i, j))
      {
        v = 1;
      }
      else
      {
        v = 0;
      }
      index_char = nb / 6;
      index = nb % 6;
      result[index_char] |= (v << (5 - index));
      ++nb;
    }
  }
  fputc(63 + n, fi); /* nb of vertices */
  for (i=0; i<taille; ++i)
  { /* then we print the adj matrix */
    fputc(result[i] + 63, fi);
  }
  fputc('\n', fi);
}



bool has_cycle_mask(graph* g, int n, set mask, bool directed)
/* check is the sub(di)graph induced by mask has a cycle or not */
{
  int u,v,w;
  // fprintf(stderr, "is_acyclic? n = %d; mask = %x \n", n, mask);

  set visited = EMPTY;
  set in_progress = EMPTY;

  char parent[n];
  if (!directed)
  {
    for (u=0; u<n; ++u)
    {
      parent[u] = 255;
    }
  }
 
  int stack[n];
  int top = -1; /* top of the stack */

  set gv; /* current list of successors */
 
  while ((u=MIN_SET(~visited & ~in_progress & mask))<n)
  {
    // fprintf(stderr, "IN(%d, %x)? %d \n", u, mask, IN(u, mask));
    /* we push u */
    ++top;
    stack[top] = u;
    in_progress |= SINGLETON(u);
    // fprintf(stderr, "--> we push %d \n", u);

    while (top>=0) /* while the stack is not empty */
    {
      v = stack[top]; /* we process the vertex on the top */
      in_progress |= SINGLETON(v);
      // fprintf(stderr, "--> we read %d \n", v);
 
      gv = ADJ_SET(g, v) & mask;

      /* if not directed, we prevent cycle of lentgh 2 */
      if (!directed) gv &=(~SINGLETON(parent[v]));

      /* if there is a cycle */
      if ((gv & in_progress) != EMPTY) return TRUE;

      gv &= ~visited;
      if (gv != EMPTY)
      {
        w = MIN_SET(gv);
        /* we push w on the stack */
        ++top;
        stack[top] = w;
        parent[w] = v;
        // fprintf(stderr, "we push %d \n", w);
      }
      else 
      {
        --top;
        // fprintf(stderr, "we read %d \n", v);
        in_progress &= ~(SINGLETON(v));
        visited |= SINGLETON(v);
      }
    }
  }
  return FALSE;
}

bool has_cycle(graph* g, int n, bool directed)
/* check if d has a cycle */
{
  return has_cycle_mask(g, n, ALL, directed);
}

bool is_chordal_mask(graph *g, int n, set mask)
/* cf rose 1976*/
{
  /* first we compute any ordering with lexicographic bfs */
  mask &= (1<<n)-1;

  int  i;
  int u,v,w;
  int ordering[CARD(mask)];

  set unumbered = mask;
  set unumbered2;
  set gv;

  set label[n];
  for (u=0; u<n; ++u)
  {
    label[u] = EMPTY;
  }

  for (i=CARD(mask)-1; i>=0; --i)
  {
    unumbered2 = unumbered;
    /* we pick v unumbered with largest label */
    v = MIN_SET(unumbered2);
    while ((u=MIN_SET(unumbered2))<n)
    {
      unumbered2 &= ~SINGLETON(u);
      if (label[u]>label[v])
      {
        v = u;
      }
    }
    
    ordering[i] = v;
    unumbered &= ~SINGLETON(v);
    
    gv = g[v] & mask & unumbered;
    while ((w=MIN_SET(gv))<n)
    {
      gv &= ~SINGLETON(w);
      label[w] |= SINGLETON(i);
    }
  }

  /* then we check this ordering */
  
  set mask2 = mask;
  for (i=0; i<CARD(mask); ++i)
  {
    v = ordering[i];
    // fprintf(stderr, "v = %d \n", v);
    mask2 &= ~SINGLETON(v);
 
    gv = g[v] & mask2;
    while ((w=MIN_SET(gv))<n)
    {
      gv &= ~SINGLETON(w);
      // fprintf(stderr, "g[v] = %x, g[w] = %x, mask2 = %d \n", g[v], g[w], mask2);
      if ((g[v] & g[w] & mask2) != (g[v] & mask2 & ~SINGLETON(w)))
      {
        return FALSE;
      }
    }
  }
  return TRUE;
}

bool is_chordal(graph *g, int n, set mask)
{
  return is_chordal_mask(g, n, ALL);
}

bool cnbpikc(graph *g, int n, int k, set current_subgraph,
             set current_chordal, int next_vertex)
{
  if (k==0)
  {
    return (current_subgraph == EMPTY);
  }

  if (k==1)
  {
    return is_chordal_mask(g, n, current_subgraph);
  }

  if (!IN(next_vertex, current_subgraph))
  {
    return cnbpikc(g, n, k, current_subgraph, current_chordal, next_vertex + 1);
  }

  if (next_vertex > n)
  {
    if (!is_chordal_mask(g, n, current_chordal))
    {
      return FALSE;
    }
    else
    {
      current_subgraph = DIFF(current_subgraph, current_chordal);
      int t = MIN_SET(current_subgraph);
      return cnbpikc(g, n, k-1, current_subgraph, SINGLETON(t), t+1);
    }
  }

  return cnbpikc(g, n, k, current_subgraph, ADD(next_vertex, current_chordal),
                 next_vertex + 1)
         ||
         cnbpikc(g, n, k, current_subgraph, current_chordal, next_vertex + 1);

}

inline bool can_be_part_in_k_chordals(graph* g, int n, int k)
{
  return cnbpikc(g, n, k, ALL, SINGLETON(0), 1);
}

bool digirth_at_leastk(graph *d, int n, int k)
/* test if digirth(d)>=k */
{
  if (k==1) return TRUE;

  graph d2[n];

  int i;
  int v,w;
  for (v=0; v<n; ++v)
  {
    d2[v] = SINGLETON(v);
  }

  set dv;
  set dv2;

  for (i=1; i<k; ++i)
  {
    for(v=0; v<n; ++v)
    {
      dv = d2[v];
      dv2 = EMPTY;
      while ((w=MIN_SET(dv)) < n)
      {
        dv2 |= d[w];
        dv &= ~SINGLETON(w);
      }
      // fprintf(stderr, "v = %d, dv2 = %x \n", v, dv2);
      if ((dv2 & SINGLETON(v)) != EMPTY)
      {
        return FALSE;
      }
      d2[v] = dv2;
    }
  }
  return TRUE;
}


// bool is_kcol_aux(graph* d, int n, int k, set current_subgraph, set current_acyclic,
//                 int next_vertex, bool directed);
bool backtrack_aux(bool (*is_not_interesting)(graph *, int, set, bool),
                   graph* d, int n, int k, set current_subgraph,
                   set current_interesting,
                   int next_vertex, bool directed)
/* check if, in the sub(di)graph induced by current_cubgraph, the acyclic subgraph
 * induced by current_acyclic can be extended with only vertices v >= next_vertex
 * in any k dicoloration */
{
  if (k==0)
  {
    return (n==0);
  }

  if (k==1)
  {
    return !is_not_interesting(d, n, current_subgraph, directed);
  }
  
  if (next_vertex >= n)
  {
    current_subgraph = DIFF(current_subgraph, current_interesting);
    /* we fix the next vertex in the next color class
     * we compute the first non colored vertex */
    int t = __builtin_ctz(current_subgraph);
    return backtrack_aux(is_not_interesting,
                         d, n, k - 1, current_subgraph, SINGLETON(t), t+1, directed);
  }

  /* if we can not add next_vertex */
  if (!IN(next_vertex, current_subgraph) ||
      is_not_interesting(d, n, ADD(next_vertex,current_interesting),directed))
  {
    return backtrack_aux(is_not_interesting,
                         d, n, k, current_subgraph, current_interesting, next_vertex + 1,
                         directed);
  }

  /* if we can add the vertex */
  return (backtrack_aux(is_not_interesting,
                        d, n, k, current_subgraph, 
                        ADD(next_vertex, current_interesting), next_vertex + 1, directed) ||
          backtrack_aux(is_not_interesting,
                        d, n, k, current_subgraph, current_interesting, next_vertex + 1,
                        directed));
}


inline bool is_kcol(graph* d, int n, int k)
{
  return backtrack_aux(has_cycle_mask, d, n, k, ALL, SINGLETON(0), 1, TRUE); 
}

inline bool is_karb(graph* g, int n, int k)
{
  return backtrack_aux(has_cycle_mask, g, n, k, ALL, SINGLETON(0), 1, FALSE); 
}


inline bool is_kvertex_critical(graph* d, int n, int k)
{
  if (is_kcol(d, n, k-1) || !is_kcol(d, n, k))
  {
    return FALSE;
  }
  int v;
  for (v=0; v<n; ++v)
  {
    if (!backtrack_aux(has_cycle_mask, d, n, k-1, DIFF(ALL, SINGLETON(v)), EMPTY, 0, TRUE))
    {
      return FALSE;
    }
  }
  return TRUE;
}


inline bool is_kcritical(graph* d, int n, int k)
{
  if (!is_kvertex_critical(d, n ,k))
  {
    return FALSE;
  }

  graph d2[MAXN * MAXN];
  copy_graph(d, d2, n);

  int v, w;
  set gv;
  for (v=0; v<n; ++v)
  {
    gv = ADJ_SET(d,v);
    while ((w=MIN_SET(gv))<n)
    {
      gv &= ~SINGLETON(w);
      remove_edge(d2, v, w);
      if (!is_kcol(d2, n, k-1))
      {
        return FALSE;
      }
      add_edge(d2, v, w);
    }
  }
  return TRUE;
}



