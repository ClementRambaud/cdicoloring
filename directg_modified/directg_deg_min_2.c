#define MIN_IN_OUT_DEG 2

int degprune(int *indeg, int *outdeg, int v, int n)
{
  return (indeg[v] < MIN_IN_OUT_DEG) || (outdeg[v] < MIN_IN_OUT_DEG);
}

#define DEGPRUNE degprune

#include "../nauty/directg.c"

