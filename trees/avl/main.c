#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main()
{
    AVL *avl = create_AVL();

    insert_AVL(avl, 1);
    insert_AVL(avl, 2);
    insert_AVL(avl, 3);

    preOrder_AVL(avl);

    free_AVL(avl);
}