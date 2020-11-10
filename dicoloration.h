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
#define DEL(x, a) DIFF(a, SINGLETON(x))
#define MIN_SET(a) __builtin_ctz(a)
#define CARD(a) __builtin_popcount(a)

#define ADJ_SET(g, v) (g[v]) 
#define IS_ADJ(g,u,v) IN(v, ADJ_SET(g, u))

#define CEILING(p,q) (1 + ((p-1)/q))

void add_edge(graph* g, int u, int v);
void remove_edge(graph* g, int u, int v);

void empty_graph(graph* g, int n);
void copy_graph(graph* g, graph* g2, int n);

int deg_out(graph* d, int n, int v);

int deg_in(graph* d, int n, int v);

#define MIN(X,Y) (((X) < (Y)) ? (X) : (Y))
int deg_out_min(graph* d, int n);
int deg_in_min(graph* d, int n);
int deg_min(graph* g, int n);

int number_of_arcs(graph* d, int n);

void read_digraph6(FILE* fi, graph* d, int* n);
void read_graph6(FILE* fi, graph* g, int* n);
void print_graph(FILE* fi, graph* g, int n);
void write_digraph6(FILE* fi, graph* d, int n);
void write_graph6(FILE* fi, graph* g, int n);

#define NONVISITED 0
#define VISITED    1
#define INPROGRESS 2

bool has_cycle_mask(graph* g, int n, set mask, bool oriented);
bool has_cycle(graph* g, int n, bool oriented);

bool is_kcol_aux(graph* d, int n, int k, set current_subgraph,
                 set current_acyclic, int next_vertex, bool oriented);

bool is_kcol(graph* d, int n, int k);
bool is_karb(graph* g, int n, int k);

bool is_kvertex_critical(graph* d, int n, int k);
bool is_kcritical(graph* d, int n, int k);


