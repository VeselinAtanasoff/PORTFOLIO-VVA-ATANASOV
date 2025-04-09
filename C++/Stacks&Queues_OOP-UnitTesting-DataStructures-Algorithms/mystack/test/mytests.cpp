#include "MyStack.h"
#include "gtest/gtest.h"

class metaTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
 
  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

TEST_F(metaTest, myStackPush) {
  MyStack stack(4);
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  EXPECT_EQ(0, stack.myStackPush(&a));
  EXPECT_EQ(0, stack.myStackPush(&b));
  EXPECT_EQ(0, stack.myStackPush(&c));
  EXPECT_EQ(0, stack.myStackPush(&d));
  EXPECT_EQ(4, stack.myStackNoOfElem());
}

TEST_F(metaTest, myStackPushNullptr) {
  MyStack stack(4);
  int* a = nullptr;
  EXPECT_EQ(1, stack.myStackPush(a));
}

TEST_F(metaTest, myStackPop1) {
  MyStack stack(4);
  int a = 1;
  int b = 2;
  int c = 3;
  stack.myStackPush(&a);
  stack.myStackPush(&b);
  stack.myStackPush(&c);
  EXPECT_EQ(3, stack.myStackNoOfElem());
  int d;
  stack.myStackPop(&d);
  EXPECT_EQ(3, d);
  EXPECT_EQ(2, stack.myStackNoOfElem());
}

TEST_F(metaTest, myStackPopAll) {
  MyStack stack(4);
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  stack.myStackPush(&a);
  stack.myStackPush(&b);
  stack.myStackPush(&c);
  stack.myStackPush(&d);
  int e;
  int f;
  int g;
  int h;
  EXPECT_EQ(0, stack.myStackPop(&e));
  EXPECT_EQ(0, stack.myStackPop(&f));
  EXPECT_EQ(0, stack.myStackPop(&g));
  EXPECT_EQ(0, stack.myStackPop(&h));
  EXPECT_EQ(0, stack.myStackNoOfElem());
}

TEST_F(metaTest, myStackPopEmpty) {
  MyStack stack(4);
  int a;
  EXPECT_EQ(1, stack.myStackPop(&a));
}

TEST_F(metaTest, myStackDestroy) {
  MyStack stack(4);
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  stack.myStackPush(&a);
  stack.myStackPush(&b);
  stack.myStackPush(&c);
  stack.myStackPush(&d);
  stack.myStackDestroy();
  EXPECT_EQ(0, stack.myStackNoOfElem());
}

TEST_F(metaTest, dataExtractedProperly) {
  MyStack stack(4);
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  stack.myStackPush(&a);
  stack.myStackPush(&b);
  stack.myStackPush(&c);
  stack.myStackPush(&d);
  int e;
  int f;
  int g;
  int h;
  stack.myStackPop(&e);
  stack.myStackPop(&f);
  stack.myStackPop(&g);
  stack.myStackPop(&h);
  EXPECT_EQ(4, e);
  EXPECT_EQ(3, f);
  EXPECT_EQ(2, g);
  EXPECT_EQ(1, h);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return  RUN_ALL_TESTS();
}


