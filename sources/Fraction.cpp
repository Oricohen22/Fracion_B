
#include "Fraction.hpp"

namespace ariel
{

    Fraction::Fraction()
    {
        Numerator = 0;
        Denominator = 1;
        
    }

    Fraction::Fraction(int a, int b)
    {
        if (b == 0)
        {
            throw std ::invalid_argument("Invalid Denominator argument");
        }
        (this)->Numerator = a;
        (this)->Denominator = b;
        reduce();
        minus();
    }

    Fraction::Fraction(float number)
    {
        if (number == 0)
        {
            Numerator = 0;
            Denominator = 1;
        }
        else
        {
            int sign = 1;
            if (number < 0)
                sign = -1;
            Numerator = abs(number) * 1000 * sign;
            Denominator = 1000;
        }
        reduce();
        minus();
    }

    int Fraction::getNumerator() const
    {
        return this->Numerator;
    }

    int Fraction::getDenominator() const
    {
        return this->Denominator;
    }

    void Fraction::setNumerator(int Numerator)
    {
        this->Numerator = Numerator;
    }

    void Fraction::setDenominator(int Denominator)
    {
        if (Denominator == 0)
        {
            throw std ::invalid_argument("Invalid Denominator argument");
        }
        this->Denominator = Denominator;
    }

    void Fraction::checkFractionOverflow(long Numerator, long Denominator) const
    {
        constexpr long INT_MAX_L = static_cast<long>(std::numeric_limits<int>::max());
        constexpr long INT_MIN_L = static_cast<long>(std::numeric_limits<int>::min());

        if (Numerator < INT_MIN_L || Numerator > INT_MAX_L || Denominator < INT_MIN_L || Denominator > INT_MAX_L)
        {
            throw std::overflow_error("The numerator or the denominator are too large or small");
        }
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        long long newDenominator = (long)Denominator * other.Denominator;
        long long newNumerator = (long)Numerator * other.Denominator + (long)other.Numerator * Denominator;
        checkFractionOverflow(newNumerator, newDenominator);
        int intNewNumerator = (int)newNumerator;
        int intNewDenominator = (int)newDenominator;
        return Fraction(intNewNumerator, intNewDenominator);
    }

    Fraction operator+(float number, const Fraction &other)
    {
        Fraction numberFraction(number);
        return numberFraction + other;
    }

    Fraction
    Fraction::operator+(float number)
    {
        Fraction f(number);
        return *this + f;
    }

    // operator '-' defination
    Fraction Fraction::operator-(const Fraction &other) const
    {
        long longDenominator = (long)Denominator * other.Denominator;
        long longNumerator = (long)Numerator * other.Denominator - other.Numerator * Denominator;
        checkFractionOverflow(longNumerator, longDenominator);
        int newDenominator = Denominator * other.Denominator;
        int newNumerator = Numerator * other.Denominator - other.Numerator * Denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator-(const float number, const Fraction &other)
    {
        Fraction frac(number);
        return frac - other;
    }

   
    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.Numerator == 0)
            throw std::runtime_error("Denominator cannot be zero");

        long longNumerator = (long)Numerator * other.Denominator;
        long longDenominator = (long)other.Numerator * Denominator;
        checkFractionOverflow(longNumerator, longDenominator);

        return Fraction(Numerator * other.Denominator, Denominator * other.Numerator);
    }

    Fraction operator/(const float number, const Fraction &other)
    {
        Fraction frac(number);
        return frac / other;
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        long longDenominator = (long)Denominator * other.Denominator;
        long longNumerator = (long)Numerator * other.Numerator;
        checkFractionOverflow(longNumerator, longDenominator);
        int newNumerator = Numerator * other.Numerator;
        int newDenominator = Denominator * other.Denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator*(const float number, const Fraction &other)
    {
        Fraction frac(number);
        return frac * other;
    }
   
    bool Fraction::operator==(const Fraction &other) const
    {
        float numerator1 = static_cast<float>(this->Numerator);
        float denominator1 = static_cast<float>(this->Denominator);
        float numerator2 = static_cast<float>(other.Numerator);
        float denominator2 = static_cast<float>(other.Denominator);
        float a = numerator1 / denominator1;
        float b = numerator2 / denominator2;
        float compression = 0.001;
        return std::abs(a - b) < compression;
    }

    bool Fraction::operator==(float number) const
    {
        Fraction fraction(number);
        return *this == fraction;
    }

    bool operator==(float number, const Fraction &other)
    {
        const Fraction fraction(number);
        return other == fraction;
    }

    bool Fraction::operator!=(float number)
    {
        float firstfloat = (float)Numerator / (float)Denominator;
        if (firstfloat != number)
            return true;
        return false;
    }

    bool operator!=(float number, const Fraction &fraction)
    {

        return fraction != number;
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        int thisNumerator = Numerator;
        int thisDenominator = Denominator;
        int otherNumerator = other.Numerator;
        int otherDenominator = other.Denominator;

        // If denominator is negative, make it positive and flip numerator sign
        if (thisDenominator < 0)
        {
            thisNumerator = -thisNumerator;
            thisDenominator = -thisDenominator;
        }
        if (otherDenominator < 0)
        {
            otherNumerator = -otherNumerator;
            otherDenominator = -otherDenominator;
        }

        // Compare fractions using cross multiplication
        return thisNumerator * otherDenominator > otherNumerator * thisDenominator;
    }

    bool Fraction::operator>(float number) const
    {
        float fracValue = static_cast<float>(Numerator) / static_cast<float>(Denominator);
        return fracValue > number;
    }

    bool operator>(float number, const Fraction &frac)
    {
        float fracValue = static_cast<float>(frac.getNumerator()) / static_cast<float>(frac.getDenominator());
        return number > fracValue;
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        int thisNumerator = Numerator;
        int thisDenominator = Denominator;
        int otherNumerator = other.Numerator;
        int otherDenominator = other.Denominator;

        // If denominator is negative, make it positive and flip numerator sign
        if (thisDenominator < 0)
        {
            thisNumerator = -thisNumerator;
            thisDenominator = -thisDenominator;
        }
        if (otherDenominator < 0)
        {
            otherNumerator = -otherNumerator;
            otherDenominator = -otherDenominator;
        }

        // Compare fractions using cross multiplication
        return thisNumerator * otherDenominator < otherNumerator * thisDenominator;
    }

    bool Fraction::operator<(float number) const
    {
        Fraction numberFraction(number);
        return *this < numberFraction;
    }

    bool operator<(float number, const Fraction &other)
    {
        Fraction numberFraction(number);
        return numberFraction < other;
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return !(*this < other);
    }

   
    bool operator>=(float number, const Fraction &other)
    {
        Fraction numberFraction(number);
        return numberFraction >= other;
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return !(*this > other);
    }

    

    bool operator<=(float number, const Fraction &other)
    {
        Fraction numberFraction(number);
        std::cout << number << std::endl;
        return numberFraction <= other;
    }

    std::istream &operator>>(std::istream &stream, Fraction &fraction)
    {
        int Numerator;
        int Denominator;
        if (stream.peek() == EOF)
        {
            throw std::runtime_error("Error: wrong number of arguments");
        }
        stream >> Numerator;
        if (stream.peek() == EOF)
        {
            throw std::runtime_error("Error: wrong number of arguments");
        }
        stream >> Denominator;
        if (!Denominator)
        {
            throw std::runtime_error("Error: received zero denominator");
        }
        fraction.setNumerator(Numerator);
        fraction.setDenominator(Denominator);
        fraction.reduce();
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const Fraction &fraction)
    {
        stream << fraction.Numerator << "/" << fraction.Denominator;
        return stream;
    }

    Fraction &Fraction::operator++()
    {
        this->Numerator += this->Denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator++(int)
    {
        Fraction copyFraction = *this;
        operator++();
        reduce();
        return copyFraction;
    }

    Fraction &Fraction::operator--()
    {
        this->Numerator -= this->Denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator--(int)
    {
        Fraction copyFraction = *this;
        operator--();
        reduce();
        return copyFraction;
    }

   

    

    int Fraction::gcd(int Numerator, int Denominator)
    { // function to get greatest common divisor of two integers using recursion
        if (Numerator == 0)
        {
            return Denominator;
        }
        return gcd(Denominator % Numerator, Numerator);
    }

    void Fraction::reduce()
    {
        if(this->Denominator < 0){
            this->Numerator *= -1;
            this->Denominator *= -1;
        }

        // Get greatest common divisor of numerator and denominator
        int gcdValue = gcd(this->Numerator, this->Denominator);

        // Reduce the fraction to its simplest form
        Numerator /= gcdValue;
        Denominator /= gcdValue;
    }

    void Fraction::minus() {
    if (Denominator < 0) {
        Denominator *= -1;
        Numerator *= -1;
    } else if (Denominator == 0) {
        throw std::runtime_error("Denominator cannot be zero");
    }
}


}