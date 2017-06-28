#pragma once

namespace test
{
namespace detail
{
    class test_exception : public std::exception
    {
        virtual const char* what() const throw();
    };
}
}


