#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int main(int argc, char *argv) {
    struct lnode *a = BuildOneTwoThree();
    struct lnode *b = BuildOneTwoThree();
    printf("A\n");
    traverse(a);
    printf("B\n");
    traverse(b);
    printf("Moving\n");
    movenode(&a, &b);
    printf("A\n");
    traverse(a);
    printf("B\n");
    traverse(b);
}

