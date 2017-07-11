#pragma once
#include <utility>
#include <list>
#include <functional>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <detail/colors.hpp>
#include <detail/assert.hpp>
#include <detail/test_exception.hpp>
#include <detail/TestRunner.hpp>

#define ASSERT_EQUAL(a, b) test::detail::assert_equal_impl(a, b, #a, #b,  __LINE__, __FILE__);
#define ASSERT_EQUAL_VECTORS(a, b) test::detail::assert_equal_vectors_impl(a, b , #a, #b,  __LINE__, __FILE__);
#define NOT_IMPLEMENTED test::assert_impl(__LINE__, __FILE__);

#define IGNORE_TEST_CASE(TC) void ignore_tc_##TC()

#define TEST_CASE(TC) namespace test { struct Test_##TC               \
{                                                   \
    void execute();                                 \
                                                    \
    void registerMe()                               \
    {                                               \
        detail::TestRunner::instance().registerTest(        \
                     #TC,                           \
                     std::bind(&Test_##TC::execute, this)   \
                );                                  \
    }                                               \
                                                    \
    Test_##TC()                                          \
    {                                               \
        registerMe();                               \
    }                                               \
};                                                  \
} \
static test::Test_##TC tc_##TC;                                     \
void test::Test_##TC::execute()                                 \


#define FIXTURE_TEST_CASE(TC, Fixture) namespace test { struct Test_##TC  : public Fixture             \
{                                                   \
    void execute();                                 \
                                                    \
    void registerMe()                               \
    {                                               \
        detail::TestRunner::instance().registerTest(        \
                     #TC,                           \
                     std::bind(&Test_##TC::execute, this)   \
                );                                  \
    }                                               \
                                                    \
    Test_##TC()                                          \
    {                                               \
        registerMe();                               \
    }                                               \
};                                                  \
} \
static test::Test_##TC tc_##TC;                                     \
void test::Test_##TC::execute()                                 \


#define RUN_TESTS() test::detail::TestRunner::instance().runTests()

namespace test
{
    void assert_impl(int line_number, const char* filename);
}
