#include "pch.h"

#include "Vector.h"
#include "gtest/gtest.h"

using namespace astra;

// Test fixture class for Vector
class VectorTest : public ::testing::Test {
  protected:
    Vector* vec;

    void SetUp() override {
        vec = new Vector(3);
    }

    void TearDown() override {
        // Clean up after each test
        delete vec;
    }
};


TEST_F(VectorTest, size_initialization) {
    Vector v(5);
    EXPECT_EQ(v.getSize(), 5);
}
