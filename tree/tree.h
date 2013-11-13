/*
 * $Id$
 */
#ifndef TREE_H
#  define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    int val;
};

struct traverse_result {
    int *vals;
    int length;
};

struct traverse_result *get_dfs(struct node *tree);
struct node *maketree(int val); 
void setleft(struct node *tree, int val);
void setright(struct node *tree, int val);
int info(struct node *n);
struct node *left(struct node *n);
struct node *right(struct node *n);
void printval(struct node *node);
void printInOrder(struct node *root);
void printPostOrder(struct node *root);
void printdfs(struct node *root);
void dup_detect_and_traverse(); 
void binary_search_tree();
struct node *create_tree();
int lookup(struct node *root, int val);
struct node *insert(struct node *tree, int val);
int get_level(struct node *root, struct node *n);
struct node *create_tree();

#endif /* ifndef TREE_H */
