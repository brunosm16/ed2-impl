#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
};

BinTree *root;

BinTree *create_Tree()
{
    BinTree *root = (BinTree *)malloc(sizeof(BinTree));

    //  Memory allocated with success
    if (root != NULL)
        *root = NULL;

    return root;
}

// Libera uma struct NODE da memória
void free_Node(struct NODE *node)
{
    if (node == NULL)
        return;

    // Libera os nós mais à esquerda
    // e mais à direita recursivamente
    free_Node(node->left);
    free_Node(node->right);
    free(node);
    node = NULL;
}

void free_Tree(BinTree *root)
{
    if (root == NULL)
        return;

    // Utiliza a o método auxiliar free_node para liberar
    // cada nó da árvore
    free_Node(*root);
    free(root);
}

int isEmpty_Tree(BinTree *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return 0;
}

int height_Tree(BinTree *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int height_left = height_Tree(&((*root)->left));
    int height_right = height_Tree(&((*root)->right));

    if (height_left > height_right)
    {
        return height_left + 1;
    }
    else
    {
        return height_right + 1;
    }
}

int total_Nodes_Tree(BinTree *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int height_left = total_Nodes(&((*root)->left));
    int height_right = total_Nodes(&((*root)->right));

    return (height_left + height_right + 1);
}

void preOrder(BinTree *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        printf("%d\n", (*root)->data);
        preOrder(&((*root)->left));
        preOrder(&((*root)->right));
    }
}

void inOrder_Tree(BinTree *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        preOrder(&((*root)->left));
        printf("%d\n", (*root)->data);
        preOrder(&((*root)->right));
    }
}

void postOrder_Tree(BinTree *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        preOrder(&((*root)->left));
        preOrder(&((*root)->right));
        printf("%d\n", (*root)->data);
    }
}