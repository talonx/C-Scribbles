#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int main(int argc, char **argv) {
//    struct lnode *head = BuildOneTwoThree();
    struct lnode *head = buildlist(20, 3, 2);
    printf("Original list - traversing...\n");
    traverse(head);
    recreverse(&head);
    printf("Traversing after reverse\n");
    traverse(head);
}

