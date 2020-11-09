Small C library to deals with graph and digraph coloring.

## Dependancy ##
We use `make` and `gcc`.
The programs `nauty`, `plantri` and `surftri` are very useful but not necessary.

## Usage ##
- `is_not_karb.native k`: reads graph (graph6 format) from stdin and outputs
   only those which can not be partitionnate in k induced forests.
- `is_not_kcol.native k`: reads digraphs (digraphs6 format) from stdin
  and outputs only those which are not k-dicolorable.
- `is_kcritical.native k`: reads digraphs (digraph6 format) from stdin and 
  outputs only those which are k-dicritical.

### Example: ###
The bash script
```
geng -C -d4 8 | directg -o | ./is_kcritical.native 3
```
generates the list of 3-critical oriented graphs of order 8.

## Interface ##
The integer n allways represents the number of vertices.
### data structures ###
Graphs and digraphs are represented by adjacency matrix.
- `bool`: defined to be equal to `int`,
- `set`: representation of a set by any `int`, somme macro are given to manipulates
         these objects (`UNION`, `MIN_SET`, `SINGLETON`,...),
- `graph`: same as `set`, typical usage: `graph g[20];`,

### Functions ###
- `void add_edge(graph* g, int u, int v);`
- `void remove_edge(graph* g, int u, int v);`
- `void empty_graph(graph* g, int n);`
- `void copy_graph(graph* g, graph* g2, int n);`
- `int deg_out(graph* d, int n, int v);`
- `int deg_in(graph* d, int n, int v);`
- `int deg_out_min(graph* d, int n);`
- `int deg_in_min(graph* d, int n);`
- `int deg_min(graph* g, int n);`
- `void read_digraph6(FILE* fi, graph* d, int* n);`
- `void read_graph6(FILE* fi, graph* g, int* n);`
- `void print_graph(FILE* fi, graph* g, int n);`
- `void write_digraph6(FILE* fi, graph* d, int n);`
- `void write_graph6(FILE* fi, graph* g, int n);`
- `bool has_cycle_mask(graph* g, int n, set mask, bool oriented);`
- `bool has_cycle(graph* g, int n, bool oriented);`
- `bool is_kcol_aux(graph* d, int n, int k, set current_subgraph,
                 set current_acyclic, int next_vertex, bool oriented);`
- `bool is_kcol(graph* d, int n, int k);`
- `bool is_karb(graph* g, int n, int k);`
- `bool is_kvertex_critical(graph* d, int n, int k);`
- `bool is_kcritical(graph* d, int n, int k);`


