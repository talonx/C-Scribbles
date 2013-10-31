#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    int val;
};

struct node *maketree(int val) {
    struct node *n = malloc(sizeof (struct node));
    assert (n != NULL);
    n->val = val;
    return n;
}

void setleft(struct node *tree, int val) {
    tree->left = maketree(val);
}

void setright(struct node *tree, int val) {
    tree->right = maketree(val);
}

int info(struct node *n) {
    return n->val;
}

struct node *left(struct node *n) {
    return n->left;
}

struct node *right(struct node *n) {
    return n->right;
}

void printval(struct node *node) {
    printf("%d\n", node->val);
}

void printInOrder(struct node *root) {
    if(root->left != NULL) {
        printInOrder(root->left);
    }
    printval(root);
    if(root->right != NULL) {
        printInOrder(root->right);
    }
}

void printPostOrder(struct node *root) {
    printf("Printing children\n");
    if(root->left != NULL) {
        printPostOrder(root->left);
    }
    if(root->right != NULL) {
        printPostOrder(root->right);
    }
    printf("End children\n");
    printval(root);
}

void printdfs(struct node *root) {
    printval(root);
    printf("Printing children\n");
    if(root->left != NULL) {
        printdfs(root->left);
    }
    if(root->right != NULL) {
        printdfs(root->right);
    }
    printf("End children\n");
}

void build_and_traverse() {
    int num;
    scanf("%d", &num);
    struct node *tree = maketree(num);
    struct node *p;
    struct node *q;

    while(num != 1000) {
        p = q = tree;
        while(num != info(p) && q != NULL) {
            p = q;
            if(num < info(p)) {
                q = left(p);
            } else {
                q = right(p);
            }
        }
        if(num == info(p)) {
            printf("%d %s\n", num, "is a duplicate");
        } else if (num < info(p)) {
            setleft(p, num);
        } else {
            setright(p, num);
        }
        scanf("%d", &num);
    }
    printf("DFS\n");
    printdfs(tree);

    printf("InOrder\n");
    printInOrder(tree);
    
    printf("PostOrder\n");
    printPostOrder(tree);
}

void binary_search_tree() {
    int num;
    scanf("%d", &num);
    struct node *tree = maketree(num);
    struct node *p;
    struct node *q;

    while(num != 1000) {
        p = q = tree;
        while(q != NULL) {
            p = q;
            if(num < info(p)) {
                q = left(p);
            } else {
                q = right(p);
            }
        }
        if(num == info(p) || num > info(p)) {
            setright(p, num);
        } else {
            setleft(p, num);
        }
        scanf("%d", &num);
    }

    printf("InOrder\n");
    printInOrder(tree);
}

int main(int argc, char **argv) {
    binary_search_tree();
    return 0;
}
