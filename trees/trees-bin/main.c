#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

int main()
{
    BinTree *tree_one = create_Tree();
    free_Tree(tree_one);
}