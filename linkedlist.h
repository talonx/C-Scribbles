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

/**
 * Deletes a list - deallocates all memory and sets the head pointer to null
 */
void deletelist(struct lnode **head) {
    struct lnode *current = *head;
    struct lnode *next;
    while(current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

/**
 * Move through the list and print out each element
 */
void traverse(struct lnode *head) {
    struct lnode *lp;
    for(lp = head;lp != NULL;lp = lp->next) {
        printf("%d\n", lp->data);
    }
}

/**
 * Deletes the head element and returns it's value
 */
int pop(struct lnode **head) {
    int ret = (*head)->data;
    free(*head);
    *head = NULL;
    return ret;
}

struct lnode *allocate(int data) {
    struct lnode *node = malloc(sizeof(struct lnode));
    node->data = data;
    return node;
}

/**
 * Inserts the given data at the specified index
 */
void insertnth(struct lnode **headref, int index, int data) {
    int n;
    struct lnode *current = *headref;
    for(n = 0;n < index - 1;n++) {
       current = current->next;
    }
    struct lnode *newnode = allocate(data);
    struct lnode *next = current->next;
    current->next = newnode;
    newnode->next = next;
}

