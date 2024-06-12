#include <algorithm>
#include <limits.h>
#include <ostream>
#include <stdexcept>

template<typename F>
class Tropical;

template<typename F>
bool operator == (const Tropical<F>& lhs, const Tropical<F>& rhs);

template<typename F>
Tropical<F> operator + (const Tropical<F>& lhs, const Tropical<F>& rhs);

template<typename F>
Tropical<F> operator * (const Tropical<F>& lhs, const Tropical<F>& rhs);

template<typename F>
Tropical<F> operator / (const Tropical<F>& lhs, const Tropical<F>& rhs);

template<typename F>
std::ostream& operator<<(std::ostream& os, const Tropical<F>& num);

template<typename F>
class Tropical {
    F val;
    bool inf;

public:
    Tropical() {
        inf = true;
        val = 0;
    }

    Tropical(const F& val, const bool inf = false) : val(val), inf(inf) {
    }

    bool IsZero() {
        return inf;
    }



    friend bool operator == <> (const Tropical&, const Tropical&);
    friend Tropical operator + <> (const Tropical&, const Tropical&);
    friend Tropical operator * <> (const Tropical&, const Tropical&);
    friend Tropical operator / <> (const Tropical&, const Tropical&);
    friend std::ostream& operator<< <> (std::ostream&, const Tropical&);
};

template<typename F>
bool operator == (const Tropical<F>& lhs, const Tropical<F>& rhs) {
    if (lhs.inf && rhs.inf) {
        return true;
    } else if (!lhs.inf && !rhs.inf) {
        return lhs.val == rhs.val;
    }
    return false;
}

template<typename F>
Tropical<F> operator + (const Tropical<F>& lhs, const Tropical<F>& rhs) {
    if (lhs.inf) {
        return rhs;
    } else if (rhs.inf) {
        return lhs;
    }
    return Tropical<F>(std::max(lhs.val, rhs.val));
}

template<typename F>
Tropical<F> operator * (const Tropical<F>& lhs, const Tropical<F>& rhs) {
    if (lhs.inf) {
        return lhs;
    }
    if (rhs.inf) {
        return rhs;
    }
    if (lhs.val > 0 && rhs.val > 0 && LLONG_MAX - rhs.val < lhs.val) {
        std::cout << lhs.val << ' ' << rhs.val << '\n';
        throw;
    } else if (lhs.val < 0 && rhs.val < 0 && LLONG_MIN - rhs.val > lhs.val) {
        std::cout << lhs.val << ' ' << rhs.val << '\n';
        throw;
    }
    return Tropical<F>(lhs.val + rhs.val);
}

template<typename F>
Tropical<F> operator / (const Tropical<F>& lhs, const Tropical<F>& rhs) {
    if (rhs.inf) {
        throw std::runtime_error("Division by tropical zero");
    }
    auto res = lhs;
    res.val -= rhs.val;
    return res;
}

template<typename F>
std::ostream& operator<<(std::ostream& out, const Tropical<F>& num) {
    if (num.inf == false) {
        out << num.val;
    } else {
        out << "-inf";
    }
    return out;
}
