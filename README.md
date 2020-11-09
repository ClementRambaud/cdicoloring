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


