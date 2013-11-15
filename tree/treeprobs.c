#include "treeprobs.h"

int isLeaf(struct node *node) {
    return node->right == NULL && node->left == NULL;
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
        if(hasPath(node->left, sum, node->left->val + running) == 1) {
            return 1;
        }
    }

    if(node->right != NULL) {
        if(hasPath(node->right, sum, node->right->val + running) == 1) {
            return 1;
        }
    }
    return 0;
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
