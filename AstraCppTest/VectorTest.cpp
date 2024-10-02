#include "pch.h"

#include "Vector.h"
#include "gtest/gtest.h"

namespace astra {

// Test fixture class for Vector
class VectorTest : public ::testing::Test {
  protected:

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(VectorTest, valid_size_input) {
    Vector v(5);
    EXPECT_EQ(v.get_size(), 5);
}

TEST_F(VectorTest, invalid_size_input) {
    EXPECT_THROW({ Vector v(0); }, std::invalid_argument);
    EXPECT_THROW({ Vector v(-5); }, std::invalid_argument);
}

TEST_F(VectorTest, array_initialization) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);
    EXPECT_EQ(v.get_size(), 3);

    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
    EXPECT_EQ(v[2], 3.0);
}

TEST_F(VectorTest, copy_constructor) {
    double arr[] = {1.0, 2.0, 3.0};

    Vector v1(arr, 3);
    Vector v2(v1);

    EXPECT_EQ(v2.get_size(), 3);

    EXPECT_EQ(v2[0], 1.0);
    EXPECT_EQ(v2[1], 2.0);
    EXPECT_EQ(v2[2], 3.0);
}

TEST_F(VectorTest, comma_initializer) { 
    Vector v(3);
    v << 1, 3, 5;

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 5);
}

TEST_F(VectorTest, access_elements) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
    EXPECT_EQ(v[2], 3.0);
}

TEST_F(VectorTest, insert_out_of_range) {
    Vector v(2);
    v << 1 << 2;

    EXPECT_THROW(v << 3, std::out_of_range);
}

TEST_F(VectorTest, index_out_of_range) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    EXPECT_THROW(v[3], std::out_of_range);
    EXPECT_THROW(v[-1], std::out_of_range);
}

TEST_F(VectorTest, vector_addition) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0, 6.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    Vector result = v1 + v2;

    EXPECT_EQ(result[0], 5.0);
    EXPECT_EQ(result[1], 7.0);
    EXPECT_EQ(result[2], 9.0);
}

} // namespace astra