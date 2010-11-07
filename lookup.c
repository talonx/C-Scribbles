/*
 * From K&R 6.6 - the given example.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define PRIME 31

struct lnode *install(char *s, char *t);
struct lnode *lookup(char *key);
unsigned hash(char *s);

struct lnode *tab[MAXSIZE];

struct lnode {
    struct lnode *next;
    char *key;
    char *value;
};

int main(int argc, char *argv) {
    install("hrishikesh", "barua");
    install("hrishikesh", "barua1");
    install("2hrishikesh", "barua2");
    install("3hrishikesh", "barua3");
    install("hrishikesh4", "barua4");
    struct lnode *res = lookup("hrishikesh");
    printf("%s\n", res == NULL ? "null" : res->value);
   // printf("%s\n", res);
    res = lookup("1hrishikesh");
    printf("%s\n", res == NULL ? "null" : res->value);
    res = lookup("2hrishikesh");
    printf("%s\n", res == NULL ? "null" : res->value);
    res = lookup("3hrishikesh");
    printf("%s\n", res == NULL ? "null" : res->value);
}

struct lnode *install(char *s, char *t) {
    unsigned loc = hash(s);
    struct lnode *list = lookup(s);
    if(list == NULL) {
        list = (struct lnode *) malloc(sizeof(*list));
        if(list == NULL || ((list->key = strdup(s)) == NULL)) {
            return NULL;
        }
        list->next = tab[loc];
        tab[loc] = list;
    } else {
        free((void *)list->value);
    }
    if((list->value = strdup(t)) == NULL) {
        return NULL;
    }
    return list;
}

struct lnode *lookup(char *key) {
    struct lnode *lp;
    for(lp = tab[hash(key)]; lp != NULL; lp = lp->next) {
        if(strcmp(key, lp->key) == 0) {
            return lp;
        }
    }
    return NULL;
}

unsigned hash(char *s) {
    unsigned h;
    for (h = 0; *s != '\0'; s++) {
        h = *s + h * PRIME;
    }
    h = h % MAXSIZE;
    //printf("%d\n", h);
    return h;
}
