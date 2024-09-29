#include "pch.h"

#include "Vector.h"
#include "gtest/gtest.h"

namespace astra {

// Test fixture class for Vector
class VectorTest : public ::testing::Test {
  protected:
    Vector* vec;

    void SetUp() override { vec = new Vector(3); }

    void TearDown() override {
        // Clean up after each test
        delete vec;
    }
};

TEST_F(VectorTest, size_initialization) {
    Vector v(5);
    EXPECT_EQ(v.get_size(), 5);
}

TEST_F(VectorTest, array_initialization) {
    double vals[] = {1.0, 2.0, 3.0};
    Vector v(vals, 3);
    EXPECT_EQ(v.get_size(), 3);
}


TEST_F(VectorTest, invalid_size_input) {
    Vector v(-5);
    EXPECT_EQ(v.get_size(), 0);
}

TEST_F(VectorTest, test_null_vector) {
    Vector v(-5);
    EXPECT_EQ(v.is_null(), true);
}

} // namespace astra