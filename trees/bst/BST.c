#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

// representa o nó da árvore
struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
};

// criar uma árvore, retornando uma raíz apontando para NULL
BST *create_BST()
{
    BST *root = (BST *)malloc(sizeof(BST));

    // memória alocada com sucesso
    if (root != NULL)
        *root = NULL;

    return root;
}

// libera um nó de uma árvore, liberando todos os nós
// mais à esquerda e mais à direita recursivamentevoid free_Node(struct NODE *node)
{
    if (node == NULL)
        return;

    // libera os nós mais à esquerda e mais à direita
    // de forma recursiva
    free_Node(node->left);
    free_Node(node->right);

    free(node);
    node = NULL;
}

// libera uma árvore binária de busca(BST)
// usando o método auxiliar free_Node
void free_BST(BST *root)
{
    if (root == NULL)
        return;

    free_Node(*root);
    free(root);
}

// percorre a árvore usando pré-ordem
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

// percorre a árvore usando em-ordem
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

// percorre a árvore usando pós-ordem
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

// verifica se uma árvore AVL é nula, caso seja
// retorna 1 senão retorna 0
int isEmpty_BST(BST *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return 0;
}

// realiza o cálculo da profundidade de uma árvore AVL
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

// cálcula a altura da árvore
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

// auxilia na remoção de um elemento em uma BST,
// tratando o caso de um filho e o de dois filhos
struct NODE *remove_Current(struct NODE *curr)
{
    struct NODE *node1, *node2;

    // 1 filho
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

int sum_Nodes(BST *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    return (*root)->data + sum_Nodes(&((*root)->left)) + sum_Nodes(&((*root)->right));
}

int total_Null_Values(BST *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return total_Null_Values(&((*root)->left)) + total_Null_Values(&((*root)->right));
}

int total_Three_Multiple(BST *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    int isMultiple = 0;

    if (root != NULL || *root != NULL)
    {
        if (((*root)->data % 3 == 0))
        {
            isMultiple = 1;
        }
    }

    if (isMultiple)
    {
        return 1 + total_Three_Multiple(&((*root)->left)) + total_Three_Multiple(&((*root)->right));
    }
    else
    {
        return 0 + total_Three_Multiple(&((*root)->left)) + total_Three_Multiple(&((*root)->right));
    }
}

int total_Leaf_Nodes(BST *root)
{
    if (root == NULL || (*root) == NULL)
        return 0;

    int isLeaf = 0;

    if ((*root)->left == NULL && (*root)->right == NULL)
        isLeaf = 1;

    if (isLeaf)
        return 1 + total_Leaf_Nodes(&((*root)->left)) + total_Leaf_Nodes(&((*root)->right));
    else
        return 0 + total_Leaf_Nodes(&((*root)->left)) + total_Leaf_Nodes(&((*root)->right));
}