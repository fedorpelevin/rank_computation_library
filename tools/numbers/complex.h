template<typename Q>
class Complex {
    Q x;
    Q y;

public:
    Complex() = default;

    Complex(Q a, Q b = 0): x(a), y(b) {
    }

    Complex(Q num) {
        x = num;
	y = 0;
    }

    Complex(const long long& num) {
        x = num;
	y = 0;
    }
    
    Complex(const std::pair<long long, long long>& pair) {
        x = pair.first;
        y = pair.second;
    }

    Q Re() const {
        return x;
    }

    Q Im() const {
        return y;
    }

    Complex Conjugate() const {
        return Complex(x, -y);
    }

    bool operator==(const Complex& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Complex& rhs) const {
        return x != rhs.x || y != rhs.y;
    }

    bool operator!=(const long long num) const {
        return (x != num) || (y != 0);
    }


    Complex operator+() const {
        return *this;
    }

    Complex operator-() const {
        return Complex(-x, -y);
    }

    Complex operator+(const Complex& b) const {
        return Complex(x + b.Re(), y + b.Im());
    }

    Complex operator-(const Complex& b) const {
        return Complex(x - b.Re(), y - b.Im());
    }

    Complex operator*(const Complex& b) const {
        return Complex(x * b.Re() - y * b.Im(), x * b.Im() + y * b.Re());
    }

    Complex operator/(const Q& b) const {
        return Complex(x / b, y / b);
    }

    Complex operator/(const Complex& b) const {
        return (*this * b.Conjugate()) / ((b * b.Conjugate()).x);
    }

    Complex& operator+=(const Complex& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Complex& operator-=(const Complex& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Complex& operator*=(const Complex& rhs) {
        *this = *this * rhs;
	return *this;
    }

    Complex& operator/=(const Complex& rhs) {
        *this = *this / rhs;
	return *this;
    }

    // I/O stream operators:
    template <typename T>
    friend std::ostream& operator<<(std::ostream&, const Complex<T>&);
};


template <typename Q>
std::ostream& operator<<(std::ostream& out, const Complex<Q>& num) {
    if (num.y == 0) {
        out << num.x;
        return out;
    }
    out << num.x << " + " << num.y << "i";
    return out;
}

/*
Complex pow(Complex& a, int deg) {
    if (deg == 0) {
        return Complex(1);
    } else if (deg == 1) {
        return a;
    } else if (deg == -1) {
        return 1 / a;
    } else if (deg % 2 == 0) {
        Complex tmp = pow(a, deg / 2);
        return tmp * tmp;
    } else {
        Complex tmp = pow(a, deg / 2);
        return tmp * tmp * a;
    }
}*/
