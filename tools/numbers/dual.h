#include <cmath>

template <typename F>
class Dual {
    F x;
    F y;

public:
    Complex() = default;

    Complex(double a, double b = F(0)): x(a), y(b) {
    }

    double Re() const {
        return x;
    }

    double Im() const {
        return y;
    }

    Complex Conjugate() const {
        return Complex(x, -y);
    }

    Complex operator += (const Dual<F>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Complex operator -= (const Dual<F>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    bool operator == (const Dual<F>& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator != (const Dual<F>& rhs) const {
        return x != rhs.x || y != rhs.y;
    }
};

template <typename F>
Dual<F> operator + (Dual<F> a) {
    return a;
}

template <typename F>
Dual operator - (Dual<F> a) {
    return Dual<F>(-a.Re(), -a.Im());
}

template <typename F>
Dual operator + (const Dual<F>& a, const Dual<F>& b) {
    return Dual<F>(a.Re() + b.Re(), a.Im() + b.Im());
}

template <typename F>
Dual operator - (const Dual<F>& a, const Dual<F>& b) {
    return Dual<F>(a.Re() - b.Re(), a.Im() - b.Im());
}

template <typename F>
Dual operator * (const Dual<F>& a, const Dual<F>& b) {
    return Dual<F>(a.Re() * b.Re() - a.Im() * b.Im(), a.Re() * b.Im() + a.Im() * b.Re());
}

template <typename F>
Dual<F> operator / (const Dual<F>& a, const F b) {
    return Dual<F>(a.Re() / b, a.Im() / b);
}

template <typename F>
Dual<F> operator / (const Dual<F>& a, const Dual<F>& b) {
    return (a * b.Conjugate()) / ((b * b.Conjugate()).Re());
}

Dual pow(Dual& a, int deg) {
    if (deg == 0) {
        return Dual<F>(F(1));
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
}
