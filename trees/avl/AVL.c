#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

struct NODE
{
    int data;
    int height;
    struct NODE *left;
    struct NODE *right;
};

AVL *root;

AVL *create_AVL()
{
    AVL *root = (AVL *)malloc(sizeof(AVL));

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

void free_AVL(AVL *root)
{
    if (root == NULL)
        return;

    // Utiliza a o método auxiliar free_node para liberar
    // cada nó da árvore
    free_Node(*root);
    free(root);
}

int isEmpty_AVL(AVL *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return 0;
}

int height_AVL(AVL *root)
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

int total_Nodes_AVL(AVL *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int height_left = total_Nodes(&((*root)->left));
    int height_right = total_Nodes(&((*root)->right));

    return (height_left + height_right + 1);
}

int height_Node(struct NODE *node)
{
    if (node == NULL)
        return -1;
    else
        return node->height;
}

int balance_Factor_Node(struct NODE *node)
{
    return labs(height_Node(node->left) - height_Node(node->right));
}

int highest_Value(int x, int y)
{
    if (x > y)
        return x;
    return y;
}

void rotate_LL(AVL *root)
{
    struct NODE *node;

    node = (*root)->left;
    (*root)->left = node->right;
    node->right = *root;

    (*root)->height = highest_Value(height_AVL((*root)->left), height_AVL((*root)->right)) + 1;

    node->height = highest_Value(height_AVL(node->left), height_AVL((*root)->height)) + 1;

    (*root) = node;
}

void rotate_RR(AVL *root)
{
    struct NODE *node;

    node = (*root)->right;
    (*root)->right = node->left;
    node->left = (*root);

    (*root)->height = highest_Value(height_AVL((*root)->left), height_AVL((*root)->right)) + 1;

    node->height = highest_Value(height_AVL(node->right), height_AVL((*root)->height)) + 1;

    (*root) = node;
}

void rotate_LR(AVL *root)
{
    rotate_RR(&(*root)->left);
    rotate_LL(root);
}

void rotate_RL(AVL *root)
{
    rotateLL(&(*root)->right);
    rotate_RR(root);
}

int insert_AVL(AVL *root, int value)
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
    // o novo nó respeitando as propriedades de uma AVL
    if (*root == NULL)
    {
        *root = new_Node;
    }
    else
    {
        struct NODE *curr = *root;
        struct NODE *prev = NULL;

        // percorre a árvore procurando o nó folha apropriado
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

// auxilia na remoção de um elemento em uma AVL
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

int remove_AVL(AVL *root, int value)
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

int find_AVL(AVL *root, int value)
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

void preOrder_AVL(AVL *root)
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

void inOrder_AVL(AVL *root)
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

void postOrder_AVL(AVL *root)
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