Small C library to deal with graph and digraph colouring.

## Complilation ##
Run `make`: it will download `nauty` and compile the needed parts of it, and then compile some useful programs (see below).

## Usage ##
- `is_not_karb.native k`: read graph (graph6 format) from stdin and output
   only those which can not be partitionnate in k induced forests.
- `is_not_kcol.native k`: read digraphs (digraphs6 format) from stdin
  and output only those which are not k-dicolourable.
- `is_kcritical.native k`: read digraphs (digraph6 format) from stdin and 
  output only those which are k-dicritical.
- `cant_be_part_in_k_chordals.native k`: read digraphs and output those which can't be partitioned into k chrodals.
- `orient_deg_min_2_digirth_4.native k`: generate all the orientation of digirth at least 4 and minimum in/out degree at least 2 of the input (Warning: there is duplicate up to isomorphism).

### Modified `nauty-directg`: ###

- `directg_min_deg_2.native -o`: read graph and output its orientation of minimum in and out
degree at least 2
- `directg_min_deg_3.native -o`: read graph and output its orientation of minimum in and out
degree at least 3

### Some scripts: ###
- `./find_3critical.sh n` write to stdout the list of 3-dicritical oriented graphs of
order n,

### Examples: ###
The bash script
```
cat file.g6 | ./is_not_karb.native 3 | ./directg_deg_min_3 -o \
            | ./is_not_kcol.native 3 > result.d6
```
writes in the file `result.d6` all the orientations of a graph in `file.g6` 
of minimum in and out degree at least 3 and not 3 dicolourable.

## Interface for dicolouration ##
The integer n allways represents the number of vertices.

### Data structures ###
Graphs and digraphs are represented by adjacency matrix.
- `bool`: defined to be equal to `int`,
- `set`: representation of a set by any `int`, some macro are given to manipulates
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


