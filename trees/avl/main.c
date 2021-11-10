#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main()
{
    AVL *avl = create_AVL();

    insert_AVL(avl, 1);
    insert_AVL(avl, 2);
    insert_AVL(avl, 3);
    insert_AVL(avl, 4);
    insert_AVL(avl, 5);
    insert_AVL(avl, 6);
    insert_AVL(avl, 7);

    preOrder_AVL(avl);

    free_AVL(avl);
}