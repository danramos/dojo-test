#include <iostream>
#include <dojo-test-tools.hpp>
#include <stdexcept>

#include <Rational.hpp>

TEST_CASE(ConstructionAndPrinting)
{
    std::cout << Rational(1, 2) << std::endl;
}

TEST_CASE(Equality)
{
    ASSERT_EQUAL(Rational(1, 2), Rational(1, 2));
    ASSERT_EQUAL(Rational(3, 4), Rational(3, 4));
    ASSERT_EQUAL(Rational(4, 5), Rational(4, 5));
}

TEST_CASE(Addition)
{
    ASSERT_EQUAL(Rational(1, 3) + Rational(2, 5), Rational(11, 15));
    ASSERT_EQUAL(Rational(2, 3) + Rational(1, 5), Rational(13, 15));
    ASSERT_EQUAL(Rational(1, 3) + Rational(3, 5), Rational(14, 15));
    ASSERT_EQUAL(Rational(1, 2) + Rational(2, 3), Rational(7, 6));
}

TEST_CASE(Negation)
{
    ASSERT_EQUAL(-Rational(1, 2), Rational(-1, 2));
}

TEST_CASE(Subtraction)
{
    ASSERT_EQUAL(Rational(3, 4) - Rational(1, 5), Rational(11, 20));
}

TEST_CASE(Simplification)
{
    // HINT: Look up "Euclidean algorithm"
    ASSERT_EQUAL(Rational(1, 2) + Rational(3, 4), Rational(5, 4));
    ASSERT_EQUAL(Rational(2, 4), Rational(1, 2));
    ASSERT_EQUAL(Rational(6, 4), Rational(3, 2));
}

TEST_CASE(Comparison)
{
    ASSERT_EQUAL(Rational(1,2) < Rational(1,3), false);
    ASSERT_EQUAL(Rational(1,2) > Rational(1,3), true);
}

TEST_CASE(DivisionByZero)
{
    try {
        Rational x{5, 0};
        std::cout << x << std::endl;

        throw std::runtime_error("above constructor should throw DivisionByZeroError");
    } catch(const std::exception& e) {
        ASSERT_EQUAL(std::string(e.what()), "DivisionByZeroError");
    }
}

TEST_CASE(Multiplication)
{
    ASSERT_EQUAL(Rational(7, 11) * Rational(3, 4), Rational(21, 44));
}

TEST_CASE(Division)
{
    ASSERT_EQUAL(Rational(9, 11) / Rational(6, 17), Rational(51, 22));
}

TEST_CASE(SubtractionOfInt)
{
    ASSERT_EQUAL(Rational(5, 7) - 2, -Rational(9, 7));
}

TEST_CASE(Final)
{
    ASSERT_EQUAL(
        (Rational(1, 13) + Rational(28, 90)) * (Rational(125, 56) - Rational(524, 24)) + (Rational(102, 28) / Rational(16, 574)) - 123,
        Rational(16033, 196560)
    );
}

int main()
{
    RUN_TESTS();
}
