#include <stdio.h>

struct lnode {
    int data;
    struct lnode *next;
};

int length(struct lnode *head) {
    int l = 0;
    struct lnode *lp = head;
    while(lp) {
        lp = lp->next;
            l++;
	}
    return l;
}

/**
Adds a new node to the front of the list and returns a pointer to it.
*/
struct lnode *push(struct lnode *head, int data) {
    struct lnode *lp = malloc(sizeof(struct lnode));
    lp->data = data;
    lp->next = head;
    return lp;
}
