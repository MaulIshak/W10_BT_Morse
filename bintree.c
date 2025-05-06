#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>


address Alokasi(infotype X)
{
  address new_node =(address) malloc(sizeof(Node));
  new_node->info = X;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;

}