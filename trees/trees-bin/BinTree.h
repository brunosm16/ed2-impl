/* Define Type */
typedef struct NODE *BinTree;

/////////////////////////
// Methods
/////////////////////////

// Cria uma árvore binária, retornando uma raíz apontando para NULL
BinTree *create_Tree();

// Libera uma árvore binária tendo como base a raíz da árvore.
void free_Tree(BinTree *root);

// Verifica se uma Árvore esta vazia, 0 caso não esteja vazia
// e 1 caso seja vazia
int isEmpty_Tree(BinTree *root);

int height_Tree(BinTree *root);

int total_Nodes_Tree(BinTree *root);

void preOrder_Tree(BinTree *root);

void inOrder_Tree(BinTree *root);

void postOrder_Tree(BinTree *root);