#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

// representa o nó da árvore
struct NODE
{
    int data;
    int height;
    struct NODE *left;
    struct NODE *right;
};

// cria uma árvore, retornando uma raíz apontando para NULL
AVL *create_AVL()
{
    AVL *root = (AVL *)malloc(sizeof(AVL));

    // memória alocada com sucesso
    if (root != NULL)
        *root = NULL;

    return root;
}

// libera um nó de uma árvore, liberando todos os nós
// mais à esquerda e mais à direita recursivamente
void free_Node(struct NODE *node)
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

// libera uma árvore AVL usando o método
// auxiliar free_Node
void free_AVL(AVL *root)
{
    if (root == NULL)
        return;

    free_Node(*root);

    free(root);
}

// verifica se uma árvore AVL é nula, caso seja
// retorna 1 senão retorna 0
int isEmpty_AVL(AVL *root)
{
    if (root == NULL || *root == NULL)
        return 1;
    return 0;
}

// realiza o cálculo da profundidade de uma árvore AVL
int calculate_Depth(AVL *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    // cálcula a altura das subárvores mais à esquerda
    // e mais à direita de forma recursiva.
    int height_left = height_AVL(&((*root)->left));
    int height_right = height_AVL(&((*root)->right));

    if (height_left > height_right)
        return height_left + 1;
    return height_right + 1;
}

// cálcula a altura da árvore AVL
int height_AVL(AVL *root)
{
    int depth = calculate_Depth(root);

    // verifica se a árvore tem profundida maior que 0
    // para não subtrair -1 e retornar um valor negativo
    if (depth != 0)
        // considera a raíz como 0 na contagem
        return depth - 1;

    return depth;
}

// retorna o número de nós da árvore AVL
int total_Nodes_AVL(AVL *root)
{
    if (root == NULL || *root == NULL)
        return 0;

    // soma os nós das árvores mais à esquerda e
    // das árvores mais à direita
    int height_left = total_Nodes_AVL(&((*root)->left));
    int height_right = total_Nodes_AVL(&((*root)->right));

    return (height_left + height_right + 1);
}

// retorna a áltura da estrutura NODE(nó)
int height_Node(struct NODE *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}

// retorna o fator de balanceamento
int balance_Factor_Node(struct NODE *node)
{
    return labs(height_Node(node->left) - height_Node(node->right));
}

// retorna o maior valor entre dois inteiros(x e y),
// método auxiliar utilizado nas rotações
int highest_Value(int x, int y)
{
    if (x > y)
        return x;
    return y;
}

// realiza a rotação LL
void rotate_LL(AVL *root)
{
    struct NODE *node;

    // realiza a rotação
    node = (*root)->left;
    (*root)->left = node->right;
    node->right = *root;

    // atualiza as alturas da subárvores e da raiz
    (*root)->height = highest_Value(height_Node((*root)->left), height_Node((*root)->right)) + 1;
    node->height = highest_Value(height_Node(node->left), (*root)->height) + 1;

    // atualiza a raíz
    (*root) = node;
}
// realiza a rotação RR
void rotate_RR(AVL *root)
{
    struct NODE *node;

    // realiza a rotação
    node = (*root)->right;
    (*root)->right = node->left;
    node->left = (*root);

    // atualiza as alturas da subárvores e da raiz
    (*root)->height = highest_Value(height_Node((*root)->left), height_Node((*root)->right)) + 1;
    node->height = highest_Value(height_Node(node->right), (*root)->height) + 1;

    // atualiza a raíz
    (*root) = node;
}

// realiza a rotação LR
void rotate_LR(AVL *root)
{
    rotate_RR(&(*root)->left);
    rotate_LL(root);
}

// realiza a rotação RL
void rotate_RL(AVL *root)
{
    rotate_LL(&(*root)->right);
    rotate_RR(root);
}

int insert_AVL(AVL *root, int value)
{
    // variável usada para verifica se um elemento
    // foi inserido com sucesso
    int is_Inserted;

    if (*root == NULL) // árvore vazia ou nó folha
    {
        // nó a ser inserido
        struct NODE *new_Node;

        new_Node = (struct NODE *)malloc(sizeof(struct NODE));

        // erro ao alocar memória para o novo nó
        if (new_Node == NULL)
            return 0;

        // atribui os valores do novo nó
        new_Node->data = value;
        new_Node->height = 0;
        new_Node->left = NULL;
        new_Node->right = NULL;
        *root = new_Node;

        return 1;
    }

    struct NODE *curr = *root;

    if (value < curr->data)
    { // insere à esquerda

        // verifica se a inserção foi realiza com sucesso
        is_Inserted = insert_AVL(&(curr->left), value);

        // inserção obteve sucesso
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
        // verifica se a inserção foi realiza com sucesso
        is_Inserted = insert_AVL(&(curr->right), value);

        // inserção obteve sucesso
        if (is_Inserted == 1)
        {
            // necessário balancear a árvore
            if (balance_Factor_Node(curr) >= 2)
            {
                if ((*root)->right->data < value)
                    rotate_RR(root);
                else
                    rotate_RL(root);
            }
        }
    }
    else
    { // tentativa de inserir um valor duplicado
        printf("Duplicated value\n");
        return 0;
    }

    // atualiza a altura da árvore
    curr->height = highest_Value(height_Node(curr->left), height_Node(curr->right)) + 1;

    return is_Inserted;
}

// procura pelo menor elemento da árvore
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

// remove o nó que contém o valor(value) passado como argumento
int remove_AVL(AVL *root, int value)
{
    // valor não existente na árvore
    if (*root == NULL)
    {
        printf("Non-existent value\n");
        return 0;
    }

    // variável usada para verificar se a remoção foi realizada com sucesso
    int is_Removed;

    if (value < (*root)->data) // valor se encontra mais à esquerda
    {
        is_Removed = remove_AVL(&(*root)->left, value);

        // elemento foi removido com sucesso
        if (is_Removed == 1)
        {
            // necessário fazer o balanceamento da árvore
            if (balance_Factor_Node(*root) >= 2)
            {
                // obtem a altura dos nós para verificar
                // qual o tipo de rotação necessaŕia
                int height_Node_Right_Left = height_Node((*root)->right->left);
                int height_Node_Right_Right = height_Node((*root)->right->right);

                if (height_Node_Right_Left <= height_Node_Right_Right)
                    rotate_RR(root);
                else
                    rotate_LR(root);
            }
        }
    }
    else if (value > (*root)->data) // valor se encontra mais à direita
    {
        is_Removed = remove_AVL(&(*root)->right, value);

        // elemento foi removido com sucesso
        if (is_Removed == 1)
        {
            // necessário fazer o balanceamento da árvore
            if (balance_Factor_Node(*root) >= 2)
            {
                // obtem a altura dos nós para verificar
                // qual o tipo de rotação necessaŕia
                int height_Node_Left_Right = height_Node((*root)->left->right);
                int height_Node_Left_Left = height_Node((*root)->left->left);

                if (height_Node_Left_Right <= height_Node_Left_Left)
                    rotate_LL(root);
                else
                    rotate_LR(root);
            }
        }
    }
    else if ((*root)->data == value) // elemento a ser removido foi encontrado
    {
        if (((*root)->left == NULL || (*root)->right == NULL))
        { // apenas um 1 filho
            struct NODE *old_Node = (*root);

            // verifica em qual lado da árvore o elemento
            // vai ser removido
            if ((*root)->left != NULL)
                *root = (*root)->left;
            else
                *root = (*root)->right;

            free(old_Node);
        }
        else
        { // 2 filhos 
            // procura o menor nó da subárvore à direita
            struct NODE *temp_Node = (find_Lower_Node(*root)->right);

            // atualiza o valor da raíz com o valor 
            // do menor nó da subárvore à direita
            (*root)->data = temp_Node->data;

            // remove o valor do menor nó da subárvore 
            // à direita, pois agora ele se encontra na raíz
            remove_AVL(&(*root)->right, (*root)->data);

            // necessário balancear a árvore
            if (balance_Factor_Node(*root) >= 2)
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

// procura um determinado valor(value) passa como argumento
int find_AVL(AVL *root, int value)
{
    if (root == NULL)
        return 0;

    struct NODE *curr = *root;

    while (curr != NULL)
    {   
        // valor encontrado
        if (curr->data == value)
            return 1;

        // verifica em qual lado da árvore o valor
        // está localizado  
        if (value > curr->data)
            curr = curr->right;
        else
            curr = curr->left;
    }

    // elemento não encontrado
    return 0;
}

// percorre a árvore usando pre-ordem
void preOrder_AVL(AVL *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        printf("%d\n", (*root)->data);
        preOrder_AVL(&((*root)->left));
        preOrder_AVL(&((*root)->right));
    }
}

// percorre a árvore usando em-ordem
void inOrder_AVL(AVL *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        inOrder_AVL(&((*root)->left));
        printf("%d\n", (*root)->data);
        inOrder_AVL(&((*root)->right));
    }
}

// percorre a árvore usando pós-ordem
void postOrder_AVL(AVL *root)
{
    if (root == NULL)
        return;

    if (*root != NULL)
    {
        postOrder_AVL(&((*root)->left));
        postOrder_AVL(&((*root)->right));
        printf("%d\n", (*root)->data);
    }
}