#include <detail/TestRunner.hpp>
#include <detail/colors.hpp>
#include <detail/test_exception.hpp>
#include <iostream>

namespace test {
namespace detail {

void TestRunner::registerTest(const std::string& label, const std::function<void()>& tc)
    {
        _tests.push_back(std::make_pair(label, tc));
    }

    void TestRunner::runTests()
    {
        auto count = 0u;
        for (const auto& tc: _tests) {
            std::cout << CGREEN << BOLD("[START ] ") << tc.first << "" << CWHITE << std::endl;
            try {
                tc.second();

                std::cout << CGREEN << BOLD("[PASSED] ") << tc.first << "" << CWHITE << std::endl;
                std::cout << std::endl;
                count++;
            } catch(const detail::test_exception& e) {
                std::cout << CRED << BOLD("[FAILED] ") << tc.first << "" << CWHITE << std::endl;
                std::cout << std::endl;
            } catch(const no_impl_exception& e) {
                std::cout << CRED << BOLD("[FAILED] ") << tc.first << "" << CWHITE << std::endl;
                std::cout << std::endl;
            } catch(const std::exception& e) {
                std::cout << CRED << BOLD("[ERROR ] ") << "Uncaught exception: " << e.what() << std::endl;
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
}
}
