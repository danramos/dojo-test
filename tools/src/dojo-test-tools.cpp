#include <dojo-test-tools.hpp>

namespace test
{
    void assert_impl(int line_number, const char* filename)
    {
        std::cout << CRED << BOLD("[ERROR] ") << CWHITE << "Missing implementation at line " << filename<< ":" << line_number
                  << std::endl;

        throw detail::no_impl_exception();
    }
}
