#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int main(int argc, char *argv) {
    struct lnode *head = BuildOneTwoThree();
    deletelist(&head);
    printf("Deleted. Traversing...\n");
    traverse(head);
    printf("Traversal complete\n");
}

