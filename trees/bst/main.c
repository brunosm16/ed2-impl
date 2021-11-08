#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

int main()
{
    BST *arv_Bin = create_BST();

    insert_BST(arv_Bin, 8);
    insert_BST(arv_Bin, 4);
    insert_BST(arv_Bin, 2);
    insert_BST(arv_Bin, 6);
    insert_BST(arv_Bin, 12);
    insert_BST(arv_Bin, 10);
    insert_BST(arv_Bin, 14);

    // inOrder_BST(arv_Bin);
    // preOrder_BST(arv_Bin);
    postOrder_BST(arv_Bin);

    free_BST(arv_Bin);
}