#pragma once
#include <stdexcept>

namespace test
{
namespace detail
{
    class test_exception : public std::exception
    {
        virtual const char* what() const throw();
    };

    class no_impl_exception : public std::exception
    {
        virtual const char* what() const throw();
    };
}
}


