#include "LinkedList.h"
#include "gtest/gtest.h"
 
class LinkedListTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
 
  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};
 
TEST_F(LinkedListTest, addFirst) {
  LinkedList list;
  EXPECT_EQ(0, list.addFirst(1));
  EXPECT_EQ(0, list.addFirst(2));
  EXPECT_EQ(2, list.getHeadValue());
  EXPECT_EQ(1, list.getTailValue());
}

TEST_F(LinkedListTest, addLast) {
  LinkedList list;
  EXPECT_EQ(0, list.addLast(1));
  EXPECT_EQ(0, list.addLast(2));
  EXPECT_EQ(1, list.getHeadValue());
  EXPECT_EQ(2, list.getTailValue());
}

TEST_F(LinkedListTest, addAfter) {
  LinkedList list;
  list.addFirst(1);
  list.addLast(3);
  EXPECT_EQ(0, list.addAfter(1, 2));
  EXPECT_EQ(-1, list.addAfter(4, 5)); // Element 4 does not exist
  list.showList();
}

TEST_F(LinkedListTest, removeFirst) {
  LinkedList list;
  list.addFirst(1);
  list.addLast(2);
  EXPECT_EQ(0, list.removeFirst());
  EXPECT_EQ(2, list.getHeadValue());
  EXPECT_EQ(0, list.removeFirst());
  EXPECT_EQ(-1, list.removeFirst()); // List is now empty
}

TEST_F(LinkedListTest, removeLast) {
  LinkedList list;
  list.addFirst(1);
  list.addLast(2);
  EXPECT_EQ(0, list.removeLast());
  EXPECT_EQ(1, list.getTailValue());
  EXPECT_EQ(0, list.removeLast());
  EXPECT_EQ(-1, list.removeLast()); // List is now empty
}

TEST_F(LinkedListTest, removeAfter) {
    LinkedList list;
  list.addFirst(1);
  list.addLast(2);
  list.addLast(3);
  EXPECT_EQ(0, list.removeAfter(1));
  EXPECT_EQ(-1, list.removeAfter(3)); // No element after 3
  EXPECT_EQ(-1, list.removeAfter(4)); // Element 4 does not exist
    list.showList();
}




