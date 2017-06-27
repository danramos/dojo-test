#include <iostream>
#include <dojo-test-tools.hpp>
#include <stdexcept>

TEST_CASE(SimpleTest)
{
    ASSERT_EQUAL(true, true);
}

TEST_CASE(AssertionError)
{
    ASSERT_EQUAL(false, true);
}

TEST_CASE(Exception)
{
    throw std::runtime_error("some exception");
}

TEST_CASE(ExpectException)
{
    throw std::runtime_error("some exception");
}


int main()
{
    RUN_TESTS();
}
