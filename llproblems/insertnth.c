#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int main(int argc, char *argv) {
    struct lnode *head = BuildOneTwoThree();
    printf("Original list - traversing...\n");
    printf("Traversing after inserting 15 at pos 1\n");
    traverse(head);
    insertnth(&head, 1, 15);
    printf("Traversing after inserting 15 at pos 1\n");
    traverse(head);
}

