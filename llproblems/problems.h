struct lnode *BuildOneTwoThree() {
    struct lnode *head = NULL;
    struct lnode *second = NULL;
    struct lnode *third = NULL;
    
    third = push(NULL, 3);
    second = push(third, 2);
    head = push(second, 1);
    return head;
}

