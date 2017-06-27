#include <dojo-test-tools.hpp>

namespace test
{
    const char* test_exception::what() const throw()
    {
        return "AssertionError";
    }

    const char* no_impl_exception::what() const throw()
    {
        return "NotImplementedError";
    }

    void assert_impl(int line_number, const char* filename)
    {
        std::cout << CRED << BOLD("[ERROR] ") << CWHITE << "Missing implementation at line " << filename<< ":" << line_number
                  << std::endl;

        throw no_impl_exception();
    }

    void TestRunner::registerTest(const std::string& label, const std::function<void()>& tc)
    {
        _tests.push_back(std::make_pair(label, tc));
    }

    void TestRunner::runTests()
    {
        for (const auto& tc: _tests) {
            std::cout << CGREEN << BOLD("[START ] ") << tc.first << "" << CWHITE << std::endl;
            try {
                tc.second();

                std::cout << CGREEN << BOLD("[PASSED] ") << tc.first << "" << CWHITE << std::endl;
                std::cout << std::endl;
            } catch(const test_exception& e) {
                std::cout << CRED << BOLD("[FAILED] ") << tc.first << "" << CWHITE << std::endl;
                std::cout << std::endl;
            } catch(const no_impl_exception& e) {
                std::cout << CRED << BOLD("[FAILED] ") << tc.first << "" << CWHITE << std::endl;
                std::cout << std::endl;
            }
        }
    }
}
