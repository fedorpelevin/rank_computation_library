#include <ostream>
#include <utility>
#include "bigint.hpp"

class Rational {
    BigInt numerator;
    BigInt denominator;

public:
    // Constructors:
    Rational();
    Rational(const Rational&);
    Rational(const long long&);
    Rational(const long long&, const long long&);
    Rational(const std::pair<long long, long long>&);
    Rational(const BigInt&);
    Rational(const BigInt&, const BigInt&);
    Rational(const std::pair<BigInt, BigInt>&);
    
    void Simplify();

    // Assignment operators:
    Rational& operator=(const Rational&);
    Rational& operator=(const long long&);
    Rational& operator=(const std::pair<long long, long long>&);
    Rational& operator=(const BigInt&);
    Rational& operator=(const std::pair<BigInt, BigInt>&);


    // Unary arithmetic operators:
    Rational operator+() const;
    Rational operator-() const;

    // Binary arithmetic operators:
    Rational operator+(const Rational&) const;
    Rational operator-(const Rational&) const;
    Rational operator*(const Rational&) const;
    Rational operator/(const Rational&) const;
    Rational operator+(const long long&) const;
    Rational operator-(const long long&) const;
    Rational operator*(const long long&) const;
    Rational operator/(const long long&) const;
    Rational operator+(const BigInt&) const;
    Rational operator-(const BigInt&) const;
    Rational operator*(const BigInt&) const;
    Rational operator/(const BigInt&) const;
    Rational operator+(const std::pair<long long, long long>&) const;
    Rational operator-(const std::pair<long long, long long>&) const;
    Rational operator*(const std::pair<long long, long long>&) const;
    Rational operator/(const std::pair<long long, long long>&) const;
    Rational operator+(const std::pair<BigInt, BigInt>&) const;
    Rational operator-(const std::pair<BigInt, BigInt>&) const;
    Rational operator*(const std::pair<BigInt, BigInt>&) const;
    Rational operator/(const std::pair<BigInt, BigInt>&) const;

    // Arithmetic-assignment operators:
    Rational& operator+=(const Rational&);
    Rational& operator-=(const Rational&);
    Rational& operator*=(const Rational&);
    Rational& operator/=(const Rational&);
    Rational& operator+=(const long long&);
    Rational& operator-=(const long long&);
    Rational& operator*=(const long long&);
    Rational& operator/=(const long long&);
    Rational& operator+=(const BigInt&);
    Rational& operator-=(const BigInt&);
    Rational& operator*=(const BigInt&);
    Rational& operator/=(const BigInt&);
    Rational& operator+=(const std::pair<long long, long long>&);
    Rational& operator-=(const std::pair<long long, long long>&);
    Rational& operator*=(const std::pair<long long, long long>&);
    Rational& operator/=(const std::pair<long long, long long>&);
    Rational& operator+=(const std::pair<BigInt, BigInt>&);
    Rational& operator-=(const std::pair<BigInt, BigInt>&);
    Rational& operator*=(const std::pair<BigInt, BigInt>&);
    Rational& operator/=(const std::pair<BigInt, BigInt>&);

    // Increment and decrement operators:
    Rational& operator++();       // pre-increment
    Rational& operator--();       // pre-decrement
    
    // Relational operators:
    bool operator<(const Rational&) const;
    bool operator>(const Rational&) const;
    bool operator<=(const Rational&) const;
    bool operator>=(const Rational&) const;
    bool operator==(const Rational&) const;
    bool operator!=(const Rational&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const long long&) const;
    bool operator>(const long long&) const;
    bool operator<=(const long long&) const;
    bool operator>=(const long long&) const;
    bool operator==(const long long&) const;
    bool operator!=(const long long&) const;
    bool operator<(const std::pair<long long, long long>&) const;
    bool operator>(const std::pair<long long, long long>&) const;
    bool operator<=(const std::pair<long long, long long>&) const;
    bool operator>=(const std::pair<long long, long long>&) const;
    bool operator==(const std::pair<long long, long long>&) const;
    bool operator!=(const std::pair<long long, long long>&) const;
    bool operator<(const std::pair<BigInt, BigInt>&) const;
    bool operator>(const std::pair<BigInt, BigInt>&) const;
    bool operator<=(const std::pair<BigInt, BigInt>&) const;
    bool operator>=(const std::pair<BigInt, BigInt>&) const;
    bool operator==(const std::pair<BigInt, BigInt>&) const;
    bool operator!=(const std::pair<BigInt, BigInt>&) const;


    // I/O stream operators:
    friend std::ostream& operator<<(std::ostream&, const Rational&);
};


// Euclidean algorithm to find gcd. We use it to make numerator and denominator coprime.
BigInt EuclideanAlgorithm(BigInt a, BigInt b) {
    if (a < b) {
        std::swap(a, b);
    }

    while (b != 0) {
	a = a % b;
	std::swap(a, b);
    }
    return a;
}

void Rational::Simplify() {
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
    BigInt gcd;
    if (numerator > 0) {
        gcd = EuclideanAlgorithm(numerator, denominator);
    } else {
        gcd = EuclideanAlgorithm(-numerator, denominator);
    }
    numerator /= gcd;
    denominator /= gcd;
}

// Constructors definition:
Rational::Rational() {
    numerator = 0;
    denominator = 1;
}

Rational::Rational(const Rational& number) {
    numerator = number.numerator;
    denominator = number.denominator;
}

Rational::Rational(const long long& number) : numerator(number) {
    denominator = 1;
}

Rational::Rational(const long long& numerator, const long long& denominator) : numerator(numerator), denominator(denominator) {
}

Rational::Rational(const std::pair<long long, long long>& pair) {
    numerator = pair.first;
    denominator = pair.second;
}

Rational::Rational(const BigInt& k) : numerator(k) {
    denominator = 1;
}

Rational::Rational(const BigInt& numerator, const BigInt& denominator) : numerator(numerator), denominator(denominator) {
}

Rational::Rational(const std::pair<BigInt, BigInt>& pair) {
    numerator = pair.first;
    denominator = pair.second;
}

// Assignment operators definition
Rational& Rational::operator=(const Rational& number) {
    numerator = number.numerator;
    denominator = number.denominator;
    return *this;
}

Rational& Rational::operator=(const long long& k) {
    numerator = k;
    denominator = 1;
    return *this;
}

Rational& Rational::operator=(const std::pair<long long, long long>& pair) {
    numerator = pair.first;
    denominator = pair.second;
    return *this;
}

Rational& Rational::operator=(const BigInt& k) {
    numerator = k;
    denominator = 1;
    return *this;
}

Rational& Rational::operator=(const std::pair<BigInt, BigInt>& pair) {
    numerator = pair.first;
    denominator = pair.second;
    return *this;
}


// Unary operators definition
Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    Rational temp = *this;
    temp.numerator *= -1;
    return temp;
}

// Arithmetics-assignment operators definition
Rational& Rational::operator+=(const Rational& rhs) {
    const BigInt gcd = EuclideanAlgorithm(denominator, rhs.denominator);
    const BigInt c1 = rhs.denominator / gcd;
    const BigInt c2 = denominator / gcd;

    numerator = c1 * numerator + c2 * rhs.numerator;
    denominator *= c1;

    this->Simplify();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    *this += -rhs;

    this->Simplify();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;

    this->Simplify();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.numerator == 0) {
        throw;
    }

    numerator *= rhs.denominator;
    denominator *= rhs.numerator;

    this->Simplify();
    return *this;
}

Rational& Rational::operator+=(const long long& k) {
    Rational rhs = k;
    *this += rhs;
    return *this;
}

Rational& Rational::operator-=(const long long& k) {
    Rational rhs = k;
    *this -= rhs;
    return *this;
}

Rational& Rational::operator*=(const long long& k) {
    Rational rhs = k;
    *this *= rhs;
    return *this;
}

Rational& Rational::operator/=(const long long& k) {
    Rational rhs = k;
    *this /= rhs;
    return *this;
}

Rational& Rational::operator+=(const BigInt& k) {
    Rational rhs = k;
    *this += rhs;
    return *this;
}

Rational& Rational::operator-=(const BigInt& k) {
    Rational rhs = k;
    *this -= rhs;
    return *this;
}

Rational& Rational::operator*=(const BigInt& k) {
    Rational rhs = k;
    *this *= rhs;
    return *this;
}

Rational& Rational::operator/=(const BigInt& k) {
    Rational rhs = k;
    *this /= rhs;
    return *this;
}

Rational& Rational::operator+=(const std::pair<long long, long long>& pair) {
    Rational rhs = pair;
    *this += rhs;
    return *this;
}

Rational& Rational::operator-=(const std::pair<long long, long long>& pair) {
    Rational rhs = pair;
    *this -= rhs;
    return *this;
}

Rational& Rational::operator*=(const std::pair<long long, long long>& pair) {
    Rational rhs = pair;
    *this *= rhs;
    return *this;
}

Rational& Rational::operator/=(const std::pair<long long, long long>& pair) {
    Rational rhs = pair;
    *this /= rhs;
    return *this;
}

Rational& Rational::operator+=(const std::pair<BigInt, BigInt>& pair) {
    Rational rhs = pair;
    *this += rhs;
    return *this;
}

Rational& Rational::operator-=(const std::pair<BigInt, BigInt>& pair) {
    Rational rhs = pair;
    *this -= rhs;
    return *this;
}

Rational& Rational::operator*=(const std::pair<BigInt, BigInt>& pair) {
    Rational rhs = pair;
    *this *= rhs;
    return *this;
}

Rational& Rational::operator/=(const std::pair<BigInt, BigInt>& pair) {
    Rational rhs = pair;
    *this /= rhs;
    return *this;
}

// Binary arithmetic operators definition

Rational Rational::operator+(const Rational& rhs) const {
    Rational tmp = *this;
    tmp += rhs;

    tmp.Simplify();
    return tmp;
}

Rational Rational::operator-(const Rational& rhs) const {
    Rational tmp = *this;
    tmp -= rhs;

    tmp.Simplify();
    return tmp;
}

Rational Rational::operator*(const Rational& rhs) const {
    Rational tmp = *this;
    tmp *= rhs;

    tmp.Simplify();
    return tmp;
}

Rational Rational::operator/(const Rational& rhs) const {
    Rational tmp = *this;
    tmp /= rhs;

    tmp.Simplify();
    return tmp;
}

Rational Rational::operator+(const long long& k) const {
    Rational rhs = k;
    return *this + rhs;
}

Rational Rational::operator-(const long long& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp -= rhs;
    return tmp;
}

Rational Rational::operator*(const long long& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp *= rhs;
    return tmp;
}

Rational Rational::operator/(const long long& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp /= rhs;
    return tmp;
}

Rational Rational::operator+(const BigInt& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp += rhs;
    return tmp;
}

Rational Rational::operator-(const BigInt& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp -= rhs;
    return tmp;
}

Rational Rational::operator*(const BigInt& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp *= rhs;
    return tmp;
}

Rational Rational::operator/(const BigInt& k) const {
    Rational rhs = k;
    Rational tmp = *this;
    tmp /= rhs;
    return tmp;
}

Rational Rational::operator+(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp += rhs;
    return tmp;
}

Rational Rational::operator-(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp -= rhs;
    return tmp;
}

Rational Rational::operator*(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp *= rhs;
    return tmp;
}

Rational Rational::operator/(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp /= rhs;
    return tmp;
}

Rational Rational::operator+(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp += rhs;
    return tmp;
}

Rational Rational::operator-(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp -= rhs;
    return tmp;
}

Rational Rational::operator*(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp *= rhs;
    return tmp;
}

Rational Rational::operator/(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    Rational tmp = *this;
    tmp /= rhs;
    return tmp;
}

// Increment Decrement
Rational& Rational::operator++() {
    numerator += denominator;

    this->Simplify();
    return *this;
}

Rational& Rational::operator--() {
    numerator -= denominator;

    this->Simplify();
    return *this;
}

/*
    Rational comparison operators definition
*/

bool Rational::operator<(const Rational& rhs) const {
    return numerator * rhs.denominator < rhs.numerator * denominator;
}
bool Rational::operator>(const Rational& rhs) const {
    return numerator * rhs.denominator > rhs.numerator * denominator;
}
bool Rational::operator<=(const Rational& rhs) const {
    return !(*this > rhs);
}
bool Rational::operator>=(const Rational& rhs) const {
    return !(*this < rhs);
}
bool Rational::operator==(const Rational& rhs) const {
    return numerator * rhs.denominator == rhs.numerator * denominator;
}
bool Rational::operator!=(const Rational& rhs) const {
    return !(*this == rhs);
}

bool Rational::operator<(const BigInt& k) const {
    Rational rhs = k;
    return *this < rhs;
}
bool Rational::operator>(const BigInt& k) const {
    Rational rhs = k;
    return *this > rhs;
}
bool Rational::operator<=(const BigInt& k) const {
    Rational rhs = k;
    return *this <= rhs;
}
bool Rational::operator>=(const BigInt& k) const {
    Rational rhs = k;
    return *this >= rhs;
}
bool Rational::operator==(const BigInt& k) const {
    Rational rhs = k;
    return *this == rhs;
}
bool Rational::operator!=(const BigInt& k) const {
    Rational rhs = k;
    return *this != rhs;
}
bool Rational::operator<(const long long& k) const {
    Rational rhs = k;
    return *this < rhs;
}
bool Rational::operator>(const long long& k) const {
    Rational rhs = k;
    return *this > rhs;
}
bool Rational::operator<=(const long long& k) const {
    Rational rhs = k;
    return *this <= rhs;
}
bool Rational::operator>=(const long long& k) const {
    Rational rhs = k;
    return *this >= rhs;
}
bool Rational::operator==(const long long& k) const {
    Rational rhs = k;
    return *this == rhs;
}
bool Rational::operator!=(const long long& k) const {
    Rational rhs = k;
    return *this != rhs;
}

bool Rational::operator<(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    return *this < rhs;
}
bool Rational::operator>(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    return *this > rhs;
}
bool Rational::operator<=(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    return *this <= rhs;
}
bool Rational::operator>=(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    return *this >= rhs;
}
bool Rational::operator==(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    return *this == rhs;
}
bool Rational::operator!=(const std::pair<long long, long long>& pair) const {
    Rational rhs = pair;
    return *this != rhs;
}
bool Rational::operator<(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    return *this < rhs;
}
bool Rational::operator>(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    return *this > rhs;
}
bool Rational::operator<=(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    return *this <= rhs;
}
bool Rational::operator>=(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    return *this >= rhs;
}
bool Rational::operator==(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    return *this == rhs;
}
bool Rational::operator!=(const std::pair<BigInt, BigInt>& pair) const {
    Rational rhs = pair;
    return *this != rhs;
}


/*
    BigInt to output stream
    -----------------------
*/

std::ostream& operator<<(std::ostream& out, const Rational& num) {
    if (num.denominator == 1) {
        out << num.numerator;
        return out;
    }
    out << "\\frac{" << num.numerator << "}{" << num.denominator << "}";
    return out;
}

