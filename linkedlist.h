#include <stdio.h>
#include <stdlib.h>

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

/**
 * Adds a new node to the front of the list, accepting
 * a pointer to the pointer to the head of the list.
 */

void pushp(struct lnode **head, int data) {
    struct lnode *lp = malloc(sizeof(struct lnode));
    lp->data = data;
    lp->next = *head;
    *head = lp; 
}

/**
 * Adds a new node to the end of the list and returns a pointer to it
 */
struct lnode *append(struct lnode *head, int data) {
    struct lnode *lp = malloc(sizeof(struct lnode));
    lp->data = data;
    struct lnode *p = head;
    while(p->next) {
        p = p->next;
    }
    p->next = lp;
    return lp;
}
