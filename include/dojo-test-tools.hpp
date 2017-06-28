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

namespace test
{
    struct TestRunner
    {
        static TestRunner& instance()
        {
            static TestRunner instance;
            return instance;
        }

        void registerTest(const std::string& label, const std::function<void()>& tc)
        {
            _tests.push_back(std::make_pair(label, tc));
        }

        void runTests()
        {
            auto count = 0u;
            for (const auto& tc: _tests) {
                std::cout << CGREEN << BOLD("[START ] ") << tc.first << "" << CWHITE << std::endl;
                try {
                    tc.second();

                    std::cout << CGREEN << BOLD("[PASSED] ") << tc.first << "" << CWHITE << std::endl;
                    std::cout << std::endl;
                    count++;
                } catch(detail::test_exception& e) {
                    std::cout << CRED << BOLD("[FAILED] ") << tc.first << "" << CWHITE << std::endl;
                    std::cout << std::endl;
                } catch(std::exception& e) {
                    std::cout << CRED << BOLD("[ERROR ]") <<  " Uncaught exception: " << e.what() <<std::endl;
                    std::cout << CRED << BOLD("[FAILED] ") << tc.first << "" << CWHITE << std::endl;
                    std::cout << std::endl;
                }
            }
            std::cout << "Summary: ";
            if (count == _tests.size())
            {
                std::cout << CGREEN << "All " << count << " tests passed." << RST << std::endl;
            } else {
                std::cout << CRED << count << "/" << _tests.size() << " tests passed." << RST << std::endl;
            }

        }
        std::list<std::pair<std::string, std::function<void()>>>  _tests;
    };
}

#define RUN_TESTS() test::TestRunner::instance().runTests()
