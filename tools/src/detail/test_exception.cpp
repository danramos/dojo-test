#include <detail/test_exception.hpp>

namespace test
{
namespace detail
{

const char* test_exception::what() const throw()
{
    return "AssertionError";
}

const char* no_impl_exception::what() const throw()
{
    return "NotImplementedError";
}

}
}





