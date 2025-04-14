#include "Core/Core.h"
#include <gtest/gtest.h>

TEST(CoreTests, HelloWorldTest) {
  // You can't directly test the output of PrintHelloWorld,
  // but this is a placeholder for your actual tests
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}