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
    rotate_LL(&(*root)->right);
    rotate_RR(root);
}

int insert_AVL(AVL *root, int value)
{
    if (root == NULL)
        return 0;

    int is_Inserted;

    if (*root == NULL) // árvore vazia ou está em um nó folha
    {
        struct NODE *new_Node;

        new_Node = (struct NODE *)malloc(sizeof(struct NODE));

        // erro ao alocar memória para o novo nó
        if (new_Node == NULL)
            return 0;

        new_Node->data = value;
        new_Node->height = 0;
        new_Node->left = NULL;
        new_Node->right = NULL;
        *root = new_Node;

        return 1;
    }

    struct NODE *curr = *root;

    if (value < curr->data)
    { // insere a esquerda
        is_Inserted = insert_AVL(&(curr->left), value);

        // elemento foi inserido com sucesso
        if (is_Inserted == 1)
        {
            // necessário balancear a árvore
            if (balance_Factor_Node(curr) >= 2)
            {
                if (value < (*root)->left->data)
                    rotate_LL(root);
                else
                    rotate_LR(root);
            }
        }
    }
    else if (value > curr->data) // insere a direita
    {
        is_Inserted = insert_AVL(&(curr->right), value);

        if (is_Inserted == 1)
        {
            if (balance_Factor_Node(curr) >= 2)
            {
                if ((*root)->right->data > value)
                    rotate_RR(root);
                else
                    rotate_RL(root);
            }
        }
    }
    else
    {
        printf("This value already exists\n");
        return 0;
    }

    curr->height = highest_Value(height_Node(curr->left), height_Node(curr->right)) + 1;

    return is_Inserted;
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

// trata de nó com dois filhos
struct NODE *find_Lower_Node(struct NODE *curr)
{
    struct NODE *node1 = curr;
    struct NODE *node2 = curr->left;

    while (node2 != NULL)
    {
        node1 = node2;
        node2 = node2->left;
    }

    return node1;
}

int remove_AVL(AVL *root, int value)
{
    if (*root == NULL)
    {
        printf("Non-existent value\n");
        return 0;
    }

    int is_Removed;

    if (value < (*root)->data)
    {
        is_Removed = remove_AVL(&(*root)->left, value);

        if (is_Removed == 1)
        {
            if (balance_Factor_Node(*root) >= 2)
            {
                int height_Node_Right_Left = height_Node((*root)->right->left);
                int height_Node_Right_Right = height_Node((*root)->right->right);

                if (height_Node_Right_Left <= height_Node_Right_Right)
                    rotate_RR(root);
                else
                    rotate_LR(root);
            }
        }
    }
    else if (value > (*root)->data)
    {
        is_Removed = remove_AVL(&(*root)->right, value);

        if (is_Removed == 1)
        {
            if (balance_Factor_Node(*root) >= 2)
            {
                int height_Node_Left_Right = height_Node((*root)->left->right);
                int height_Node_Left_Left = height_Node((*root)->left->left);

                if (height_Node_Left_Right <= height_Node_Left_Left)
                    rotate_LL(root);
                else
                    rotate_LR(root);
            }
        }
    }
    else if ((*root)->data == value)
    { // elemento a ser removido foi encontrado
        if (((*root)->left == NULL || (*root)->right == NULL))
        { // apenas um 1 filho
            struct NODE *old_Node = (*root);

            if ((*root)->left != NULL)
                *root = (*root)->left;
            else
                *root = (*root)->right;

            free(old_Node);
        }
        else
        {
            struct NODE *temp_Node = (find_Lower_Node(*root)->right);
            (*root)->data = temp_Node->data;

            remove_AVL(&(*root)->right, (*root)->data);

            if (balance_Factor_Node((*root) >= 2))
            {
                if (height_Node((*root)->left->right) <= height_Node((*root)->left->left))
                    rotate_LL(root);
                else
                    rotate_LR(root);
            }
        }

        return 1;
    }

    return is_Removed;
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