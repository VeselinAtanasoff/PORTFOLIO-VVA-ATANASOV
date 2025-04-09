#include "MyStack.h"
#include "MyQueue.h"
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

/* A simple example framework of a Unit Test */
TEST_F(metaTest, myQueueEnqueue){
  MyQueue *q = new MyQueue(sizeof(int));
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;
  EXPECT_EQ(0, q->myQueueEnqueue(&a));
  EXPECT_EQ(0, q->myQueueEnqueue(&b));
  EXPECT_EQ(0, q->myQueueEnqueue(&c));
  EXPECT_EQ(0, q->myQueueEnqueue(&d));
  EXPECT_EQ(0, q->myQueueEnqueue(&e));
}

TEST_F(metaTest, mqQueueDequeue){
  MyQueue *q = new MyQueue(sizeof(int));
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;
  int f = 6;
  EXPECT_EQ(0, q->myQueueEnqueue(&a));
  EXPECT_EQ(0, q->myQueueEnqueue(&b));
  EXPECT_EQ(0, q->myQueueEnqueue(&c));
  EXPECT_EQ(0, q->myQueueEnqueue(&d));
  EXPECT_EQ(0, q->myQueueEnqueue(&e));
  EXPECT_EQ(0, q->myQueueDequeue(&f));
  EXPECT_EQ(1, f);
  EXPECT_EQ(0, q->myQueueDequeue(&f));
  EXPECT_EQ(2, f);
  EXPECT_EQ(0, q->myQueueDequeue(&f));
  EXPECT_EQ(3, f);
  EXPECT_EQ(0, q->myQueueDequeue(&f));
  EXPECT_EQ(4, f);
  EXPECT_EQ(0, q->myQueueDequeue(&f));
  EXPECT_EQ(5, f);
  EXPECT_EQ(1, q->myQueueDequeue(&f));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return  RUN_ALL_TESTS();
}


