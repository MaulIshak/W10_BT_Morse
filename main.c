#include <stdio.h>
#include "bintree.h"

int main()
{
  BinTree tree = NULL;
  BuildTree(&tree);

  PrintTree(tree, 5);

  
  return 0;
}
