#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
};

BST *root;

BST *create_BST()
{
    BST *root = (BST *)malloc(sizeof(BST));

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

void free_BST(BST *root)
{
    if (root == NULL)
        return;

    // Utiliza a o método auxiliar free_node para liberar
    // cada nó da árvore
    free_Node(*root);
    free(root);
}

int isEmpty_BST(BST *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return 0;
}

int height_BST(BST *root)
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

int total_Nodes_BST(BST *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int height_left = total_Nodes(&((*root)->left));
    int height_right = total_Nodes(&((*root)->right));

    return (height_left + height_right + 1);
}

int insert_BST(BST *root, int value)
{
    if (root == NULL)
        return 0;

    struct NODE *new_Node;

    new_Node = (struct NODE *)malloc(sizeof(struct NODE));

    // erro ao alocar espaço para o novo nó
    if (new_Node == NULL)
        return 0;

    new_Node->data = value;
    new_Node->left = NULL;
    new_Node->right = NULL;

    // se a árvore for vazia aponta para o novo nó, senão insere
    // o novo nó respeitando as propriedades de uma BST
    if (*root == NULL)
    {
        *root = new_Node;
    }
    else
    {
        struct NODE *curr = *root;
        struct NODE *prev = NULL;

        // percorre a árvore procurando o nó folho apropriado
        // para inserir o novo elemento
        while (curr != NULL)
        {
            // nó folha em que o elemento será inserido
            prev = curr;

            // elemento já existe
            if (value == curr->data)
            {
                free(new_Node);
                return 0;
            }

            if (value > curr->data)
                curr = curr->right;
            else
                curr = curr->left;
        }

        // realiza a inserção do novo elemento
        if (value > curr->data)
            prev->right = prev;
        else
            prev->left = prev;
    }
    return 1;
}

void preOrder_BST(BST *root)
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

void inOrder_BST(BST *root)
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

void postOrder_BST(BST *root)
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