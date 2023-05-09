#pragma once

#include <iostream>
#include "Fraction.hpp"
#include <algorithm>
#include <cmath>
#include <limits.h>

using namespace std;
namespace ariel
{

    class Fraction
    {
    private:
        int Numerator;
        int Denominator;
        void reduce();

    public:
        Fraction();
        Fraction(int, int);
        Fraction(float number);
        // Fraction(const Fraction &Fother);

        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int);
        void setDenominator(int);

        void checkFractionOverflow(long Numerator, long Denominator) const;

        // Fraction operators

        //+operators;
        Fraction operator+(const Fraction &)const;
        friend Fraction operator+(float, const Fraction &);
        Fraction operator+(float);

        // -operators
        Fraction operator-(const Fraction &)const;
        friend Fraction operator-(float, const Fraction &);
        // friend Fraction operator-(const Fraction &, float);

        // '/'operator
        Fraction operator/(const Fraction &)const;
        friend Fraction operator/(float, const Fraction &);

        //* operator
        Fraction operator*(const Fraction &)const;
        friend Fraction operator*(float, const Fraction &);
        

        // ***copersions operator***
        bool operator==(const Fraction &other) const;
        bool operator==(float number) const;
        friend bool operator==(float number, const Fraction &other);

        friend bool operator!=(float value, const Fraction &fraction);
        bool operator!=(float value);

        bool operator>(const Fraction &) const;
        friend bool operator>(float, const Fraction &);
        bool operator>(float) const;

        bool operator<(const Fraction &) const;
        bool operator<(float) const;
        friend bool operator<(float number, const Fraction &other);

        bool operator>=(const Fraction &other) const;
        friend bool operator>=(float number, const Fraction &other);

        bool operator<=(const Fraction &other) const;
        friend bool operator<=(float number, const Fraction &other);

        Fraction operator++(int);
        Fraction operator--(int);
        Fraction &operator++();
        Fraction &operator--();

        friend std::ostream &operator<<(std::ostream &stream, const Fraction &other); // output stream operator
        friend std::istream &operator>>(std::istream &stream, Fraction &other);       // input stream operator

        int gcd(int, int);
        void minus();

        
    };
}