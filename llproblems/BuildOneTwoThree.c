#include <stdio.h>
#include <stdlib.h>
#include "../linkedlist.h"
#include "problems.h"

void traverse(struct lnode *head);

int main(int argc, char *argv[]) {
        struct lnode *head = BuildOneTwoThree();
	
	traverse(head);
	
	printf("%s%d\n", "Length is ", length(head));

        struct lnode *last = append(head, 4);
        printf("After appending\n");
        traverse(head);
       
        pushp(&head, 5);
        printf("After appending using push p2p\n");
        traverse(head);

}

