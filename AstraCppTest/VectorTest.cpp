#include "pch.h"

#include "Vector.h"
#include "gtest/gtest.h"

#include "Exceptions.h"
#include "MathUtils.h"

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
    EXPECT_THROW({ Vector v(0); }, astra::internals::exceptions::invalid_size);
    EXPECT_THROW({ Vector v(-5); }, astra::internals::exceptions::invalid_size);
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

    EXPECT_THROW(v << 3, astra::internals::exceptions::init_out_of_range);
}

TEST_F(VectorTest, index_out_of_range) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    EXPECT_THROW(v[3], astra::internals::exceptions::index_out_of_range);
    EXPECT_THROW(v[-1], astra::internals::exceptions::index_out_of_range);
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

TEST_F(VectorTest, vector_addition_invalid_size) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 2);

    EXPECT_THROW(v1 + v2, astra::internals::exceptions::vector_size_mismatch);
}


TEST_F(VectorTest, vector_subtraction) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0, 6.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    Vector result = v1 - v2;

    EXPECT_EQ(result[0], -3.0);
    EXPECT_EQ(result[1], -3.0);
    EXPECT_EQ(result[2], -3.0);
}

TEST_F(VectorTest, vector_subtraction_invalid_size) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 2);

    EXPECT_THROW(v1 - v2, astra::internals::exceptions::vector_size_mismatch);
}

TEST_F(VectorTest, vector_dot) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0, 6.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    double result = v1 * v2;

    EXPECT_EQ(result, 32.0);
    
}

TEST_F(VectorTest, vector_dot_invalid_size) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 2);

    EXPECT_THROW(v1 * v2, astra::internals::exceptions::vector_size_mismatch);
}

TEST_F(VectorTest, cross_product) {
    double arr1[] = {1.0, 0.0, 0.0};
    double arr2[] = {0.0, 1.0, 0.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    Vector result = v1 ^ v2;

    EXPECT_EQ(result[0], 0.0);
    EXPECT_EQ(result[1], 0.0);
    EXPECT_EQ(result[2], 1.0);
}

TEST_F(VectorTest, cross_product_invalid_size) {
    double arr1[] = {1.0, 0.0, 0.0};
    double arr2[] = {0.0, 1.0};
    Vector v1(arr1, 2);
    Vector v2(arr2, 2);

    EXPECT_THROW(v1 ^ v2, astra::internals::exceptions::cross_product_size_error);
}

TEST_F(VectorTest, scalar_multiplication_positive) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    Vector result = v * 2;

    EXPECT_EQ(result[0], 2.0);
    EXPECT_EQ(result[1], 4.0);
    EXPECT_EQ(result[2], 6.0);
}

TEST_F(VectorTest, scalar_multiplication_negative) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    Vector result = v * -2;

    EXPECT_EQ(result[0], -2.0);
    EXPECT_EQ(result[1], -4.0);
    EXPECT_EQ(result[2], -6.0);
}

TEST_F(VectorTest, scalar_division_positive) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    Vector result = v / 2;

    EXPECT_EQ(result[0], 0.5);
    EXPECT_EQ(result[1], 1.0);
    EXPECT_EQ(result[2], 1.5);
}
  
TEST_F(VectorTest, scalar_division_negative) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    Vector result = v / -1;

    EXPECT_EQ(result[0], -1.0);
    EXPECT_EQ(result[1], -2.0);
    EXPECT_EQ(result[2], -3.0);
}

TEST_F(VectorTest, scalar_division_zero) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    EXPECT_THROW(v / 0, astra::internals::exceptions::zero_division);
}

TEST_F(VectorTest, copy_assignment_deep_copy) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0, 6.0};

    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    v1 = v2; 

    EXPECT_EQ(v1[0], 4.0);
    EXPECT_EQ(v1[1], 5.0);
    EXPECT_EQ(v1[2], 6.0);
}

TEST_F(VectorTest, copy_assignment_self_assignment) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);

    v = v; 

    EXPECT_EQ(v[0], 1.0);
    EXPECT_EQ(v[1], 2.0);
    EXPECT_EQ(v[2], 3.0);
}

TEST_F(VectorTest, copy_assignment_different_sizes) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0};

    Vector v1(arr1, 3);
    Vector v2(arr2, 2);

    v1 = v2;

    EXPECT_EQ(v1.get_size(), 2);
    EXPECT_EQ(v1[0], 4.0);
    EXPECT_EQ(v1[1], 5.0);

    EXPECT_THROW(v1[2], astra::internals::exceptions::index_out_of_range);
}

TEST_F(VectorTest, equality_operator_valid) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {1.0, 2.0, 3.0};

    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    EXPECT_TRUE(v1 == v2);
}

TEST_F(VectorTest, equality_operator_different_sizes) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {1.0, 2.0};

    Vector v1(arr1, 3);
    Vector v2(arr2, 2);

    EXPECT_FALSE(v1 == v2);
}

TEST_F(VectorTest, inequality_operator_valid) {
    double arr1[] = {1.0, 2.0, 3.0};
    double arr2[] = {4.0, 5.0, 6.0};

    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    EXPECT_TRUE(v1 != v2);
}

TEST_F(VectorTest, equality_operator_floating_point_precision) {
    double arr1[] = {1.000000001, 2.000000001, 3.000000001};
    double arr2[] = {1.0, 2.0, 3.0};

    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    EXPECT_TRUE(v1 == v2);
}

TEST_F(VectorTest, magnitude_normal_vector) {
    double arr[] = {3.0, 4.0};
    Vector v(arr, 2);
    EXPECT_DOUBLE_EQ(v.magnitude(), 5.0);
}

TEST_F(VectorTest, magnitude_zero_vector) {
    double arr[] = {0.0, 0.0, 0.0}; 
    Vector v(arr, 3);
    EXPECT_DOUBLE_EQ(v.magnitude(), 0.0);
}

TEST_F(VectorTest, magnitude_single_element_vector) {
    double arr[] = {5.0}; 
    Vector v(arr, 1);
    EXPECT_DOUBLE_EQ(v.magnitude(), 5.0);
}

TEST_F(VectorTest, magnitude_large_vector) {
    double arr[] = {1.0, 2.0, 2.0}; 
    Vector v(arr, 3);
    EXPECT_DOUBLE_EQ(v.magnitude(), 3.0);
}

TEST_F(VectorTest, magnitude_negative_components) {
    double arr[] = {-3.0, -4.0}; 
    Vector v(arr, 2);
    EXPECT_DOUBLE_EQ(v.magnitude(), 5.0);
}

TEST_F(VectorTest, angle_almost_parallel_vectors) {
    double arr1[] = {1.0, 0.0, 0.0};
    double arr2[] = {0.9999999, 0.0, 0.0};
    Vector v1(arr1, 3);
    Vector v2(arr2, 3);

    double result = astra::angle(v1, v2);

    EXPECT_NEAR(result, 0.0, 1e-7); 
}

TEST_F(VectorTest, angle_almost_opposite_vectors) {
    double arr1[] = {1.0, 0.0, 0.0};
    double arr2[] = {-1.0000001, 0.0, 0.0}; 
    Vector v1(arr1, 3);
    Vector v2(arr2, 3);
  
    double result = astra::angle(v1, v2);
    EXPECT_NEAR(result, astra::internals::mathutils::PI, 1e-7); 
}

TEST_F(VectorTest, Sum_positive) {
    double arr[] = {1.0, 2.0, 3.0};
    Vector v(arr, 3);
    EXPECT_DOUBLE_EQ(v.sum(), 6.0);
}

TEST_F(VectorTest, Sum_negative) {
    double arr[] = {-1.0, -2.0, -3.0};
    Vector v(arr, 3);
    EXPECT_DOUBLE_EQ(v.sum(), -6.0);
}

} // namespace astra