#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

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

/**
 * In order traversal of a binary tree and prints out all the values.
 */
void printInOrder(struct node *root) {
    if(root->left != NULL) {
        printInOrder(root->left);
    }
    printval(root);
    if(root->right != NULL) {
        printInOrder(root->right);
    }
}

/**
 * Post order traversal of a binary tree and prints out all the values.
 */
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

int put_val(struct node *n, int *vals, int counter) {
    vals[counter++] = n->val;
    if(n->left != NULL) {
        counter = put_val(n->left, vals, counter);
    }
    if(n->right != NULL) {
        counter = put_val(n->right, vals, counter);
    }
    return counter;
}

/**
 * Returns an array of ints in DFS order for the specified tree.
 */
struct traverse_result *get_dfs(struct node *root) {
    int *vals = malloc(100 * sizeof(int));
    int counter = 0;
    int size = put_val(root, vals, counter);
    struct traverse_result *res = malloc(sizeof (struct traverse_result));
    res->vals = vals;
    res->length = size;
    return res;
}

/**
 * DFS of a binary tree and prints out all the values.
 */
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

void dup_detect_and_traverse() {
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

/**
 * Accepts input from stdin to create a BST, stops accepting input when 1000
 * is entered (1000 is not part of the tree). Prints out an inorder traversal
 * of the tree.
 */
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

/**
 * Creates a binary search tree with hardcoded values.
 */
struct node *create_tree() {
    int vals[11] = {14, 15, 4, 9, 7, 18, 3, 5, 16, 20, 17};
    int i;
    int num;
    struct node *tree = maketree(vals[0]);
    struct node *p;
    struct node *q;
    for (i = 1;i < 11;i++) {
        num = vals[i];
        p = q = tree;
        while(q != NULL) {
            p = q;
            if(num < info(p)) {
                q = left(p);
            } else {
                q = right(p);
            }
        }
        if(num >= info(p)) {
            setright(p, num);
        } else {
            setleft(p, num);
        }
    }
    return tree;
}

/**
 * Inserts the new value specified into the existing binary search tree
 * and returns a pointer to the new tree root.
 */
struct node *insert(struct node *tree, int val) {
    if(tree == NULL) {
        return maketree(val);
    } else {
        if(val < tree->val) {
            tree->left = insert(tree->left, val);
        } else {
            tree->right = insert(tree->right, val);
        }
        return tree;
    }
}

/**
 * Looks up the node with the specified value and returns
 * a 1 if it's found anywhere in the tree, 0 otherwise. Note that
 * there might be multiple nodes with that value. This is NOT a binary
 * search tree, just a binary tree.
 */
int lookup(struct node *root, int val) {
    if(root == NULL) {
        return 0;
    }
    if(root->val == val) {
        return 1;
    }
    if(lookup(root->left, val) == 1) {
        return 1;
    }
    if(lookup(root->right, val) == 1) {
        return 1;
    }
    return 0;
}

/*
 * Incomplete
 */
int get_level(struct node *root, struct node *n) {
    int v = n->val;
    if(root->val == v) {
        return 0;
    }
    return 0;
}

/*
int main(int argc, char **argv) {
    struct node *t = create_tree();
    struct traverse_result *res = get_dfs(t);
    int *vals = res->vals;
    printf("Got dfs\n");
    int i = 0;
    for(i = 0;i < res->length;i++) {
        printf("%d\n", vals[i]);
    }
 //   printf("%d\n", lookup(t, 14));
   // printf("%d\n", lookup(t, 5));
  //  printf("%d\n", lookup(t, 18));
//    printf("%d\n", lookup(t, 100));
   //printdfs(t);
 //dup_detect_and_traverse();
    return 0;
}

*/
