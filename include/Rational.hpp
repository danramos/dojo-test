#pragma once

#include <iostream>

class Rational {
public:
    Rational(int, int);
    bool operator==(const Rational&) const;
    Rational operator+(const Rational&) const;
    Rational operator-() const;
    Rational operator-(const Rational&) const;
    Rational operator-(int) const;
    Rational operator*(const Rational&) const;
    Rational operator/(const Rational&) const;
    bool operator<(const Rational&) const;
    bool operator>(const Rational&) const;
};

std::ostream& operator<< (std::ostream&, const Rational&);
