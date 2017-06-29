#pragma once
#include <list>
#include <functional>

namespace test
{
namespace detail
{

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
}
