#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int count(struct lnode *head, int searchFor);

int main(int argc, char *argv) {
    struct lnode *head = BuildOneTwoThree();
    int i = count(head, 2);
    printf("%d\n", i);
}

int count(struct lnode *head, int searchFor) {
    struct lnode *lp = head;
    int count = 0;
    while(lp) {
        if(lp->data == searchFor) {
            count++;
        }
        lp = lp->next;
    }
    return count;
}
