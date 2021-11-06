/* Define Type */
typedef struct NODE *BST;

/////////////////////////
// Methods
/////////////////////////

// Cria uma árvore binária, retornando uma raíz apontando para NULL
BST *create_BST();

// Verifica se uma Árvore esta vazia, 0 caso não esteja vazia
// e 1 caso seja vazia
int isEmpty_BST(BST *root);

int height_BST(BST *root);

int total_Nodes_BST(BST *root);

int insert_BST(BST *root, int value);

int remove_BST(BST *root, int value);

int find_BST(BST *root, int value);

// Libera uma árvore binária tendo como base a raíz da árvore.
void free_BST(BST *root);

void preOrder_BST(BST *root);

void inOrder_BST(BST *root);

void postOrder_BST(BST *root);