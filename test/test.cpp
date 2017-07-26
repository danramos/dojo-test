#include <dojo-test-tools.hpp>
#include <LookAndSay.hpp>
#include <iostream>

/**
 * Make each test case pass without using loops.
 */
TEST_CASE(NextOfASingleNumberIsOneOfThatNumber)
{
    ASSERT_EQUAL("11", LookAndSay::next("1"));
    ASSERT_EQUAL("12", LookAndSay::next("2"));
    ASSERT_EQUAL("13", LookAndSay::next("3"));
}

TEST_CASE(NextOfSameTwoNumbersIs2OfThatNumber)
{
    ASSERT_EQUAL("21", LookAndSay::next("11"));
    ASSERT_EQUAL("22", LookAndSay::next("22"));
    ASSERT_EQUAL("23", LookAndSay::next("33"));
}

TEST_CASE(TwoDifferentNumbers)
{
    ASSERT_EQUAL("1112", LookAndSay::next("12"));
    ASSERT_EQUAL("1213", LookAndSay::next("23"));
    ASSERT_EQUAL("1211", LookAndSay::next("21"));
}

TEST_CASE(ThreeSameNumbers)
{
    ASSERT_EQUAL("31", LookAndSay::next("111"));
    ASSERT_EQUAL("32", LookAndSay::next("222"));
    ASSERT_EQUAL("33", LookAndSay::next("333"));
}

TEST_CASE(ThreeNumbersAllDifferent)
{
    ASSERT_EQUAL("111213", LookAndSay::next("123"));
    ASSERT_EQUAL("121113", LookAndSay::next("213"));
    ASSERT_EQUAL("131211", LookAndSay::next("321"));
}

TEST_CASE(ThreeNumbersTwoConsecutiveTheSame)
{
    ASSERT_EQUAL("2112", LookAndSay::next("112"));
    ASSERT_EQUAL("1122", LookAndSay::next("122"));
}

/**
 *  Refactor your code to be more generic.
 *  Tests must not break during this process.
 *  Make small transformations in your code that would lead you into a writing a loop
 */

TEST_CASE(GeneratedSequence)
{
    ASSERT_EQUAL("11", LookAndSay::next("1"));
    ASSERT_EQUAL("21", LookAndSay::next("11"));
    ASSERT_EQUAL("1211", LookAndSay::next("21"));
    ASSERT_EQUAL("111221", LookAndSay::next("1211"));
    ASSERT_EQUAL("312211", LookAndSay::next("111221"));
    ASSERT_EQUAL("13112221", LookAndSay::next("312211"));
}



int main()
{
    RUN_TESTS();
}
