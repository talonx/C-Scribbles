/*
 *
 */
#ifndef TREEPROBS_H
#  define TREEPROBS_H
#include "tree.h"

/**
  * A "root-to-leaf path" is a sequence of nodes in a tree starting with the root node and proceeding downward to
  * a leaf (a node with no children). Given a binary tree and a sum, return true if the tree has a root-to-leaf 
  * path such that adding up all the values along the path equals the given sum. Return false if no such path can   * be found.
  */
int hasPathSum(struct node *tree, int sum);

#endif /* ifndef TREEPROBS_H */
