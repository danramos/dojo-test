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

#define ASSERT_EQUAL(a, b) test::detail::assert_equal_impl(a, b, #a, #b,  __LINE__, __FILE__);
#define NOT_IMPLEMENTED test::assert_impl(__LINE__, __FILE__);

#define IGNORE_TEST_CASE(TC) void ignore_tc_##TC()

#define TEST_CASE(TC) namespace test { struct Test_##TC               \
{                                                   \
    void execute();                                 \
                                                    \
    void registerMe()                               \
    {                                               \
        TestRunner::instance().registerTest(        \
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

#define RUN_TESTS() test::TestRunner::instance().runTests()

namespace test
{
    class no_impl_exception : public std::exception
    {
        virtual const char* what() const throw();
    };
    void assert_impl(int line_number, const char* filename);

    struct TestRunner
    {
        static TestRunner& instance()
        {
            static TestRunner instance;
            return instance;
        }

        void registerTest(const std::string& label, const std::function<void()>& tc);

        void runTests();
        std::list<std::pair<std::string, std::function<void()>>>  _tests;
    };
}
