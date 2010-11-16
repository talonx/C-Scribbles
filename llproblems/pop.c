#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int main(int argc, char **argv) {
    struct lnode *head = BuildOneTwoThree();
    struct lnode *next = head->next;
    int i = pop(&head);
    printf("Values returned from deleted node %d\n", i);
    traverse(next);
}
