#pragma once
#include <stdexcept>
#include <detail/test_exception.hpp>
#include <vector>
#include <iterator>
#include <algorithm>

namespace test
{
namespace detail
{
template <typename T>
class vector_dumper
{
public:
    vector_dumper(const std::vector<T>& that) : _data(that)
    {

    }

    friend std::ostream& operator<<(std::ostream& ss, const vector_dumper& dumper)
    {
       ss << "[";
       for (auto i = 0u; i < dumper._data.size(); i++) {
            if (i != 0) {
                ss << ", " ;
            }
            ss << dumper._data[i];
       }
       ss << "]";
    }

    const std::vector<T>& _data;
};

template <typename A, typename B>
void assert_equal_impl(const A& a, const B& b,
        const char* a_label,
        const char* b_label,
        int line_number,
        const char* filename)
{
    if (!(a == b)) {
        std::cout << "\x1B[1m\x1B[31m[ERROR ] Assertion failed at line " <<filename << ":" << line_number
                  << ": \x1B[0m\n    expression: [ " << a_label << " != " << b_label
                  << " ]\n    values: [ " << a << " != " << b  << " ] " << std::endl;
        throw test_exception();
    }
}

template <typename T>
void assert_equal_vectors_impl(const std::vector<T>& a, const std::vector<T>& b,
        const char* a_label,
        const char* b_label,
        int line_number,
        const char* filename)
{
    if (a.size() != b.size()) {
        std::cout << "\x1B[1m\x1B[31m[ERROR ] Assertion failed at line " <<filename << ":" << line_number
                  << ": \x1B[0m\n"
                  << "    expression: [ " << a_label << " != " << b_label << " ]\n"
                  << "    sizes: [ " << a.size() << " != " << b.size()  << " ] " << std::endl;
        throw test_exception();
    }

    if (a != b) {
         std::cout << "\x1B[1m\x1B[31m[ERROR ] Assertion failed at line " <<filename << ":" << line_number
                  << ": \x1B[0m\n"
                  << "    expression: [ " << a_label << " != " << b_label << " ]\n"
                  << "    lvalue: " << vector_dumper<T>(a) << "\n"
                  << "    rvalue: " << vector_dumper<T>(b) << "\n";
        throw test_exception();
    }
}

} 
}

