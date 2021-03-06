#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "treeprobs.h"

int init_suite1(void)
{
    return 0;
}

int clean_suite1(void)
{
    return 0;
}

void testLookup(void) {
    struct node *t = create_tree();
    CU_ASSERT(lookup(t, 14) == 1);
    CU_ASSERT(lookup(t, 5) == 1);
    CU_ASSERT(lookup(t, 18) == 1);
    CU_ASSERT(lookup(t, 100) == 0);
}

void printarray(int *arr) {
    int i = 0;
    for (i = 0;i < 11; i++) {
        printf("%d\n", arr[i]);
    }
}

void testHasPathSum() {
    struct node *t = create_tree();
    CU_ASSERT(hasPathSum(t, 80) == 1);
    CU_ASSERT(hasPathSum(t, 21) == 1);
    CU_ASSERT(hasPathSum(t, 39) == 1);
    CU_ASSERT(hasPathSum(t, 22) == 0);
    CU_ASSERT(hasPathSum(t, 0) == 0);
    CU_ASSERT(hasPathSum(t, 100) == 0);
    CU_ASSERT(hasPathSum(NULL, 100) == 0);
}

void testInsert(void) {
    struct node *t = create_tree();
    struct node *new = insert(t, 11);
    struct traverse_result *res = get_dfs(new);
    int expected[12] = {14, 4, 3, 9, 7, 5, 11, 15, 18, 16, 17, 20};
    int *vals = res->vals;
    int i = 0;
    for(i = 0;i < res->length;i++) {
        CU_ASSERT(expected[i] == vals[i]);
    }

}

void testInsertDisplace(void) {
    struct node *t = create_tree();
    struct node *new = insert(t, 16);
    struct traverse_result *res = get_dfs(new);
    int expected[12] = {14, 4, 3, 9, 7, 5, 15, 18, 16, 17, 16, 20};
    int *vals = res->vals;
    int i = 0;
    for(i = 0;i < res->length;i++) {
        CU_ASSERT(expected[i] == vals[i]);
    }

}

void testDFS(void) {
    struct node *t = create_tree();
    int expected[11] = {14, 4, 3, 9, 7, 5, 15, 18, 16, 17, 20};
    struct traverse_result *res = get_dfs(t);
    int *vals = res->vals;
    //printarray(vals);
    int i = 0;
    for(i = 0;i < res->length;i++) {
        CU_ASSERT(expected[i] == vals[i]);
    }
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    assert(CU_add_test(pSuite, "testLookup", testLookup) != NULL);
    assert(CU_add_test(pSuite, "testDFS", testDFS) != NULL);
    assert(CU_add_test(pSuite, "testInsert", testInsert) != NULL);
    assert(CU_add_test(pSuite, "testInsertDisplace", testInsertDisplace) != NULL);
    assert(CU_add_test(pSuite, "testHasPathSum", testHasPathSum) != NULL);
    //    if ((NULL == CU_add_test(pSuite, "testLookup", testLookup)))
    //    {
    //        CU_cleanup_registry();
    //        return CU_get_error();
    //    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}


