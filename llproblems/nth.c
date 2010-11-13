#include <stdio.h>
#include "../linkedlist.h"
#include "problems.h"

int nth(struct lnode *head, int index);

int main(int argc, char *argv) {
    struct lnode *head = BuildOneTwoThree();
    int i = nth(head, 2);
    printf("%d\n", i);
}

int nth(struct lnode *head, int index) {
    struct lnode *lp = head;
    int count = 0;
    for(lp = head;lp && count < index;count++, lp = lp->next) {
    }
    return count;
}
