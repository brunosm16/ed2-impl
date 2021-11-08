#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

void find_Element(BST *arv, int val);

void check_Is_Empty(BST *arv);

void find_Element(BST *arv, int val)
{
    int exists = find_BST(arv, val);

    if (exists)
        printf("\'%d\' exists\n\n", val);
    else
        printf("\'%d\' don't exists\n\n", val);
}

void check_Is_Empty(BST *arv)
{
    int isEmpty = isEmpty_BST(arv);

    if (isEmpty)
        printf("bst is empty\n\n");
    else
        printf("bst isn't empty\n\n");
}

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
    insert_BST(arv_Bin, 16);

    // find_Element(arv_Bin, 12);

    // printf("Total Nodes : %d\n", total_Nodes_BST(arv_Bin));

    // printf("Height BST : %d\n\n", height_BST(arv_Bin));

    // remove_BST(arv_Bin, 9);
    // inOrder_BST(arv_Bin);
    // preOrder_BST(arv_Bin);
    // postOrder_BST(arv_Bin);
    // check_Is_Empty(arv_Bin);
    int lower = find_Lower_Value(arv_Bin);
    int highest = find_Highest_Value(arv_Bin);

    printf("Lower value : %d\n", lower);
    printf("Highest value : %d\n", highest);

    free_BST(arv_Bin);
}