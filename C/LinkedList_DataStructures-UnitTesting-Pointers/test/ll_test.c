#include <string.h>
#include "linkedlist.h"
#include "unity.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void) {
    // This is run before EACH test
}

void tearDown(void) {
    // This is run after EACH test
}

// Test adding first element
void test_add_first(void) {
    int ret;
    ITEM *list = NULL;

    ret = add_first(&list, 1);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, list->value);
    
    clean(&list);
}

// Test adding multiple elements at the front
void test_add_first2(void) {
    int ret;
    ITEM *list = NULL;

    ret = add_first(&list, 1);
    TEST_ASSERT_EQUAL(0, ret);
    ret = add_first(&list, 2);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(2, list->value); // Head should be 2
    TEST_ASSERT_EQUAL(1, list->next->value); // Next should be 1

    clean(&list);
}

// Test adding last element
void test_add_last(void) {
    int ret;
    ITEM *list = NULL;

    ret = add_last(&list, 1);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, list->value);
    
    clean(&list);
}

// Test adding multiple elements at the end
void test_add_last2(void) {
    int ret;
    ITEM *list = NULL;

    ret = add_last(&list, 1);
    TEST_ASSERT_EQUAL(0, ret);
    ret = add_last(&list, 2);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, list->value);
    TEST_ASSERT_EQUAL(2, list->next->value); // Next should be 2

    clean(&list);
}

// Test removing first element
void test_rem_first(void) {
    int ret;
    ITEM *list = NULL;

    add_first(&list, 1);
    add_first(&list, 2);
    
    ret = rem_first(&list);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, list->value); // Head should now be 1

    clean(&list);
}

// Test removing last element
void test_rem_last(void) {
    int ret;
    ITEM *list = NULL;

    add_first(&list, 1);
    add_first(&list, 2);
    
    ret = rem_last(&list);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(2, list->value); // Head should still be 2

    ret = rem_last(&list);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NULL(list); // List should be empty now

    clean(&list);
}

// Test removing an item after a specific item
void test_rem_after(void) {
    int ret;
    ITEM *list = NULL;

    add_first(&list, 1);
    add_first(&list, 2);
    add_last(&list, 3);

    ret = rem_after(list, list); // Remove item after 2 (which is 3)
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->next); // There should be only one item left

    clean(&list);
}

// Test adding after a specific item
void test_add_after(void) {
    int ret;
    ITEM *list = NULL;

    add_first(&list, 1);
    add_first(&list, 2);
    
    ret = add_after(list, list, 3); // Add 3 after 2
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_NOT_NULL(list->next);
    TEST_ASSERT_EQUAL(3, list->next->value); // Should be after 2

    clean(&list);
}

// Test cleaning the list
void test_clean(void) {
    ITEM *list = NULL;
    add_first(&list, 1);
    add_first(&list, 2);
    
    clean(&list);
    TEST_ASSERT_NULL(list); // List should be NULL after cleaning
}

int main (int argc, char * argv[]) {
    UnityBegin();

    /* Put your UTs here */
    MY_RUN_TEST(test_add_first);
    MY_RUN_TEST(test_add_first2);
    MY_RUN_TEST(test_add_last);
    MY_RUN_TEST(test_add_last2);
    MY_RUN_TEST(test_rem_first);
    MY_RUN_TEST(test_rem_last);
    MY_RUN_TEST(test_rem_after);
    MY_RUN_TEST(test_add_after);
    MY_RUN_TEST(test_clean);

    return UnityEnd();
}

