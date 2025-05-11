#include <stdio.h>
#include "bintree.h"

int main()
{
  BinTree tree = NULL;
  AddDaunTerkiri(&tree, 'A');
  AddDaunTerkiri(&tree, 'B');
  PrintTree(tree, 0);

  
  return 0;
}
