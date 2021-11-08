#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
};

BST *create_BST()
{
    BST *root = (BST *)malloc(sizeof(BST));

    // memory allocated with success
    if (root != NULL)
        *root = NULL;

    return root;
}

void free_Node(struct NODE *node)
{
    if (node == NULL)
        return;

    // free each node on the left and
    // on the right recursively
    free_Node(node->left);
    free_Node(node->right);

    free(node);
    node = NULL;
}

void free_BST(BST *root)
{
    if (root == NULL)
        return;

    // free each node
    free_Node(*root);

    free(root);
}

int isEmpty_BST(BST *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return 0;
}

int calculate_Depth(BST *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int height_left = calculate_Depth(&((*root)->left));
    int height_right = calculate_Depth(&((*root)->right));

    if (height_left > height_right)
        return height_left + 1;
    return height_right + 1;
}

int height_BST(BST *root)
{
    int depth = calculate_Depth(root);

    if (depth != 0)
        return depth - 1;

    return depth;
}

int total_Nodes_BST(BST *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int height_left = total_Nodes_BST(&((*root)->left));
    int height_right = total_Nodes_BST(&((*root)->right));

    return (height_left + height_right + 1);
}

int insert_BST(BST *root, int value)
{
    if (root == NULL)
        return 0;

    struct NODE *new_Node = (struct NODE *)malloc(sizeof(struct NODE));

    // erro ao alocar espaço para o novo nó
    if (new_Node == NULL)
        return 0;

    new_Node->data = value;
    new_Node->right = NULL;
    new_Node->left = NULL;

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
        if (value > prev->data)
            prev->right = new_Node;
        else
            prev->left = new_Node;
    }
    return 1;
}

// auxilia na remoção de um elemento em uma BST
struct NODE *remove_Current(struct NODE *curr)
{
    struct NODE *node1, *node2;

    if (curr->left == NULL)
    {
        node2 = curr->right;
        free(curr);
        return node2;
    }

    node1 = curr;
    node2 = curr->left;

    // procura pelo filho mais à direita
    // na subárvore da esquerda
    while (node2->right != NULL)
    {
        node1 = node2;
        node2 = node2->right;
    }

    if (node1 != curr)
    {
        node1->right = node2->left;
        node2->left = curr->left;
    }

    node2->right = curr->right;

    free(curr);

    return node2;
}

int remove_BST(BST *root, int value)
{
    if (root == NULL)
        return 0;

    struct NODE *curr = *root;
    struct NODE *prev = NULL;

    // procura pelo elemenot a ser removido
    while (curr != NULL)
    {
        // elemento a ser removido foi encontrado
        if (value == curr->data)
        {
            if (curr == *root)
                *root = remove_Current(curr);
            else
            {
                if (prev->right == curr)
                    prev->right = remove_Current(curr);
                else
                    prev->left = remove_Current(curr);
            }

            return 1;
        }

        // recebe o novo nó atual após a remoção
        prev = curr;

        if (value > curr->data)
            curr = curr->right;
        else
            curr = curr->left;
    }
}

int find_BST(BST *root, int value)
{
    if (root == NULL)
        return 0;

    struct NODE *curr = *root;

    while (curr != NULL)
    {
        if (curr->data == value)
            return 1;

        if (value > curr->data)
            curr = curr->right;
        else
            curr = curr->left;
    }

    // elemento não encontrado
    return 0;
}

int find_Lower_Value(BST *root)
{
    if (root == NULL)
        return 0;

    struct NODE *curr = *root;
    struct NODE *temp = NULL;

    while (curr != NULL)
    {
        temp = curr;
        curr = curr->left;
    }

    return temp->data;
}

int find_Highest_Value(BST *root)
{
    if (root == NULL)
        return 0;

    struct NODE *curr = *root;
    struct NODE *temp = NULL;

    while (curr != NULL)
    {
        temp = curr;
        curr = curr->right;
    }

    return temp->data;
}

void preOrder_BST(BST *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        printf("%d\n", (*root)->data);
        preOrder_BST(&((*root)->left));
        preOrder_BST(&((*root)->right));
    }
}

void inOrder_BST(BST *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        inOrder_BST(&((*root)->left));
        printf("%d\n", (*root)->data);
        inOrder_BST(&((*root)->right));
    }
}

void postOrder_BST(BST *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        postOrder_BST(&((*root)->left));
        postOrder_BST(&((*root)->right));
        printf("%d\n", (*root)->data);
    }
}