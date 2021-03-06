typedef struct NODE *BST;
BST *create_BST();
void free_BST(BST *root);
void preOrder_BST(BST *root);
void inOrder_BST(BST *root);
void postOrder_BST(BST *root);
int isEmpty_BST(BST *root);
int height_BST(BST *root);
int total_Nodes_BST(BST *root);
int insert_BST(BST *root, int value);
int remove_BST(BST *root, int value);
int find_BST(BST *root, int value);
int find_Lower_Value(BST *root);
int find_Highest_Value(BST *root);
int total_Null_Values(BST *root);
int sum_Nodes(BST *root);
int total_Three_Multiple(BST *root);
int total_Leaf_Nodes(BST *root);