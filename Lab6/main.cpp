#include <iostream>
#include "polynom.h"
#include <gtest/gtest.h>

TEST(dotTest, test1) {
    int a[] = {2, 1, 1 ,3};
    CPolynom<int[4]> poly(a);

    EXPECT_EQ(poly.calculate(1), 7);
}

TEST(dotTest, test2) {
    int a[] = {1, 1, 1};
    CPolynom<int[3]> poly(a);

    EXPECT_EQ(poly.calculate(2), 7);
}

TEST(dotTest, test3) {
    int a[] = {-2, 2};
    CPolynom<int[2]> poly(a);

    EXPECT_EQ(poly.calculate(3), -4);
}


int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
