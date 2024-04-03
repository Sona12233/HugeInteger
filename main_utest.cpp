#include "headers/HugeInt.hpp"

#include <gtest/gtest.h>

TEST(HugeInt, AdditionAndSubtractionTest)
{
    HugeInt h1(25);
    HugeInt h2(-25);
    HugeInt h3(18);
    HugeInt h4(-18);

    EXPECT_EQ(h1 + h3, 43);
    EXPECT_EQ(h1 + h4, 7);
    EXPECT_EQ(h2 + h3, -7);
    EXPECT_EQ(h2 + h4, -43);
    EXPECT_EQ(h1 - h3, 7);
    EXPECT_EQ(h1 - h4, 43);
    EXPECT_EQ(h2 - h3, -43);
    EXPECT_EQ(h2 - h4, -7);
    EXPECT_EQ(h3 - h1, -7);
}

TEST(HugeInt, MultiplicationTest)
{
    HugeInt h1(994);
    HugeInt h2(201);
    HugeInt h3(-201);
    EXPECT_EQ(h1 * h2, 199794);
    EXPECT_EQ(h1 * h3, -199794);
}

TEST(HugeInt, DivisionTset)
{
    HugeInt h1(2453);
    HugeInt h2(47);
    HugeInt h3(-47);
    EXPECT_EQ(h1 / h2, 52);
    EXPECT_EQ(h1 / h3, -52);
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
