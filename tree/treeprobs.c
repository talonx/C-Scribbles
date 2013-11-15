#include "treeprobs.h"

int isLeaf(struct node *node) {
    return node != NULL && node->right == NULL && node->left == NULL;
}

int hasPath(struct node *node, int sum, int running) {
    if(isLeaf(node)) {
        if(running == sum) {
            return 1;
        } else {
            return 0;
        }
    }

    if(node->left != NULL) {

    }

    if(node->left == NULL && tree->right == NULL) {
        if(tree->val == sum) {
            return 1;
        } else {
            return 0;
        }
    }
}

int hasPathSum(struct node *tree, int sum) {
    if(tree == NULL) {
        return 0;
    }
    if(hasPath(tree, sum, tree->val)) {
        return 1;
    }
    return 0;
}
