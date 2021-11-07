/* Define Type */
typedef struct NODE *AVL;

/////////////////////////
// Methods
/////////////////////////

// Cria uma árvore binária, retornando uma raíz apontando para NULL
AVL *create_AVL();

// Verifica se uma Árvore esta vazia, 0 caso não esteja vazia
// e 1 caso seja vazia
int isEmpty_AVL(AVL *root);

int height_AVL(AVL *root);

int height_Node(struct NODE *node);

int balance_Factor_Node(struct NODE *node);

int highest_Value(int x, int y);

void rotate_LL(AVL *root);

int total_Nodes_AVL(AVL *root);

int insert_AVL(AVL *root, int value);

int remove_AVL(AVL *root, int value);

int find_AVL(AVL *root, int value);

// Libera uma árvore binária tendo como base a raíz da árvore.
void free_AVL(AVL *root);

void preOrder_AVL(AVL *root);

void inOrder_AVL(AVL *root);

void postOrder_AVL(AVL *root);