#pragma once
#include <stdexcept>
#include <complex>
#include <iostream>
#include <vector>
#include "tools/matrix.h"
#include "w_elliptic/src/w_elliptic.hpp"


// T is a type of sequence elements. May be integer, real or complex

template <typename T>
class Sequence {
public:
    std::vector<T> forward_sequence;
    std::vector<T> backward_sequence;

    Sequence() {
    }

    ~Sequence() {
    }

    virtual T operator [] (long long n) {
        return T(0);
    }
    
    void Print(int64_t left, int64_t right) {
        for (int64_t i = left; i < right; ++i) {
            std::cout << "s_{" << i << "} = " << this->operator[](i) << '\n';
        }
    }
    
    size_t ComputeRank(int64_t matrix_size, int64_t matrix_type = 0) {
    	std::cout << "Инициализирую матрицу M" << matrix_type << " размера " << matrix_size << 'x' << matrix_size << ":\n";
    	Matrix<T> M(*this, matrix_size, matrix_type);
    	std::cout << "Вычисляю ранг матрицы M" << matrix_type << "...\n";
    	//std::cout << M0 << '\n';
    	size_t rank = M.GaussRank();
    	std::cout << "Ранг матрицы равен\t" << rank << '\n';
    	return rank;
    }
};

template <typename T>
class SomosSequence : public Sequence<T> {
    size_t k;
    std::vector<T> coefs;
public:
    using Sequence<T>::forward_sequence;
    using Sequence<T>::backward_sequence;

    SomosSequence (size_t k, const std::vector<T>& coefs, const std::vector<T>& initial_values) : k(k), coefs(coefs) {
        if (k != initial_values.size()) {
            throw std::invalid_argument("Somos-k number k differs from the number of initial values");
        }
        if (k / 2 != coefs.size()) {
            throw std::invalid_argument("Incorrect number of coefficients");
        }
        for (size_t i = 0; i < k; ++i) {
            forward_sequence.push_back(initial_values[i]);
        }
        for (size_t i = 1; i <= k; ++i) {
            backward_sequence.push_back(initial_values[k - i]);
        }
    }

    T operator [] (long long n) override {
        if (n >= 0) {
            int64_t nt = n;
            if (nt >= forward_sequence.size()) {
                for (int64_t i = forward_sequence.size(); i <= nt; ++i) {
                    T next_elem = T(0);
                    for (size_t j = 1; j <= k / 2; ++j) {
                        next_elem += (coefs[j - 1] * forward_sequence[i - j] * forward_sequence[i - k + j]);
                    }
                    next_elem = next_elem / forward_sequence[i - k];
                    
                    if (next_elem == T(0)) {
                        throw std::runtime_error("Zero element in sequence");
                    }

                    forward_sequence.push_back(next_elem);
                }
            }
            return forward_sequence[nt];
        } else {
            int64_t nt = -n + k - 1;
            if (nt >= backward_sequence.size()) {
                for (int64_t i = backward_sequence.size(); i <= nt; ++i) {
                    T next_elem = T(0);
                    for (int64_t j = 1; j <= k / 2; ++j) {
                        next_elem += (coefs[j - 1] * backward_sequence[i - j] * backward_sequence[i - k + j]);
                    }
                    next_elem = next_elem / backward_sequence[i - k];
                    
                    if (next_elem == T(0)) {
                        throw std::runtime_error("Zero element in sequence");
                    }

                    backward_sequence.push_back(next_elem);
                }
            }
            return backward_sequence[nt];
        }
    }
};

template <typename T>
class ShiftedSomosSequence : public Sequence<T> {
    SomosSequence<T>& s;
    int p;
    int k;
public:
    ShiftedSomosSequence(SomosSequence<T>& s, int p, int k) : s(s), p(p), k(k) {
    }

    T operator [] (long long n) override {
	return s[p * n + k];
    }
};

template <typename T>
class NSomosSequence : public Sequence<T> {
    SomosSequence<T> s;
public:
    NSomosSequence(SomosSequence<T>& s) : s(s) {
    }

    T operator [] (long long n) override {
        return T(n) * s(n);
    }
};

template <typename T>
class Zeta : public Sequence<T> {
    w_elliptic::we<double> w;
public:
    Zeta(const w_elliptic::we<double> &w) : w(w) {
    }

    T operator () (long long n) override {
        return w.zeta(n);
    }
};


template <typename T>
class EllipticSomos : public Sequence<T> {
    w_elliptic::we<double> w;
public:
    EllipticSomos(const w_elliptic::we<double> &w) : w(w) {
    }

    T operator [] (long long n) override {
        return w.sigma(0.5 + n) * w.zeta(0.5 + n) / std::pow(w.sigma(1.0), n * n);
    }
};


template <typename T>
class DualSomosSequence : public Sequence<T> {
    size_t k;
    SomosSequence<T> somos;
    const std::vector<T> coefs;
public:
    using Sequence<T>::forward_sequence;
    using Sequence<T>::backward_sequence;

    DualSomosSequence (size_t k, const SomosSequence<T>& somos, const std::vector<T>& coefs, const std::vector<T>& initial_values) : k(k), somos(somos), coefs(coefs) {
        if (k != initial_values.size()) {
            throw std::invalid_argument("Somos-k number k differs from the number of initial values");
        }
        for (size_t i = 0; i < k; ++i) {
            forward_sequence.push_back(initial_values[i]);
        }
        for (size_t i = 1; i <= k; ++i) {
            backward_sequence.push_back(initial_values[k - i]);
        }
    }

    T operator [] (long long n) override {
        if (n >= 0) {
            size_t nt = n;
            if (nt >= forward_sequence.size()) {
                for (size_t i = forward_sequence.size(); i <= nt; ++i) {
                    T next_elem = T(0);
		    for (size_t j = 1; j <= k / 2; ++j) {
		        next_elem += coefs[j - 1] * (somos[i - k + j] * forward_sequence[i - j] + somos[i - j] * forward_sequence[i - k + j]);
		    }
		    next_elem -= somos[i] * forward_sequence[i - k];
                    //next_elem += coefs[0] * (somos[i - 3] * forward_sequence[i - 1]) + coefs[1] * (somos[i - 2] * forward_sequence[i - 2]) + coefs[1] * (somos[i - 2] * forward_sequence[i - 2]);
                    //next_elem += coefs[0] * (somos[i - 1] * forward_sequence[i - 3]) - somos[i] * forward_sequence[i - 4];
		    //next_elem += coefs[2] * somos[i - 1] * somos[i - 3] + coefs[3] * somos[i - 2] * somos[i - 2];
                    next_elem = next_elem / somos[i - k];
                    
                    if (next_elem == T(0)) {
                        //throw std::runtime_error("Zero element in sequence");
                    }

                    forward_sequence.push_back(next_elem);
                }
                return forward_sequence[nt];
            } else {
                return forward_sequence[nt];
            }
        } else {
            int64_t nt = -n + k - 1;
            if (nt >= backward_sequence.size()) {
                for (int64_t i = backward_sequence.size(); i <= nt; ++i) {
                    int64_t n0 = 3 - i;
                    T next_elem = T(0);
		    for (size_t j = 1; j <= k / 2; ++j) {
		         next_elem += coefs[j - 1] * (somos[n0 + j] * backward_sequence[i - k + j] + somos[n0 + k - j] * backward_sequence[i - j]);
		    }
		    next_elem -= somos[n0] * backward_sequence[i - k];
                    //next_elem += coefs[0] * (somos[n0 + 1] * backward_sequence[i - 3]) + coefs[1] * (somos[n0 + 2] * backward_sequence[i - 2]) + coefs[1] * (somos[n0 + 2] * backward_sequence[i - 2]);
                    //next_elem += coefs[0] * (somos[n0 + 3] * backward_sequence[i - 1]) - somos[n0] * backward_sequence[i - 4];
		    //next_elem += coefs[2] * somos[n0 + 3] * somos[n0 + 1] + coefs[3] * somos[n0 + 2] * somos[n0 + 2];
                    next_elem = next_elem / somos[n0 + 4];
                    
                    if (next_elem == T(0)) {
                        //throw std::runtime_error("Zero element in sequence");
                    }

                    backward_sequence.push_back(next_elem);
                }
                return backward_sequence[nt];
            } else {
                return backward_sequence[nt];
            }
        }
    }
};
