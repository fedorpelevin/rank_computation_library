#pragma once
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>
#include "numbers/bigint.hpp"

BigInt factorial(BigInt n) {
    BigInt res = 1;
    for (BigInt i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

template<typename F>
class Sequence;

template<typename F>
class Matrix;

template<typename F>
std::ostream& operator << (std::ostream& os, Matrix<F>& m);

/*
    Matrix class definition.
*/
template<typename F>
class Matrix {
    std::vector<std::vector<F>> data;
public:
    Matrix() = default;
    Matrix(const std::vector<std::vector<F>>&); // Basic constructor from vector of vectors
    Matrix(const std::vector<std::vector<F>>&, const std::vector<size_t>&, const std::vector<size_t>&);
    Matrix(const Matrix<F>&, const std::vector<size_t>&, const std::vector<size_t>&); // Takes a matrix and vectors of rows and columns indices and constructs a submatrix with these indices
    Matrix(Sequence<F>&, int64_t, int64_t matrix_type=0); // Takes a sequence as an argument and constructs M0 if matrix_type=0, M1 if matrix_type=1 and throws exception else

    F LazyDeterminant() const; // F may be a semiring or semifield. Complexity is O(n * n!)
    F GaussDeterminant() const; // F requires to be a field. Complexity is O(n^3)

    size_t GaussRank() const; // F requires to be a field. Complexity is O(n^3)
    
    template<typename T>
    friend std::ostream& operator << (std::ostream&, Matrix<T>&);
};

template<typename F>
Matrix<F>::Matrix(const std::vector<std::vector<F>>& data) : data(data) {
}

template<typename F>
Matrix<F>::Matrix(const std::vector<std::vector<F>>& d, const std::vector<size_t>& rows, const std::vector<size_t>& cols) {
    data = std::vector<std::vector<F>>(rows.size(), std::vector<F>(cols.size()));
    for (size_t i = 0; i < rows.size(); ++i) {
        for (size_t j = 0; j < cols.size(); ++j) {
            data[i][j] = d[rows[i]][cols[j]];
        }
    }
}

template<typename F> 
Matrix<F>::Matrix(const Matrix& m, const std::vector<size_t>& rows, const std::vector<size_t>& cols) {
    data = std::vector<std::vector<F>>(rows.size(), std::vector<F>(cols.size()));
    for (size_t i = 0; i < rows.size(); ++i) {
        for (size_t j = 0; j < cols.size(); ++j) {
            data[i][j] = m.data[rows[i]][cols[j]];
        }
    }
}


template<typename F>
Matrix<F>::Matrix(Sequence<F>& sequence, int64_t size, int64_t matrix_type) {
    data = std::vector<std::vector<F>>(size, std::vector<F>(size));
    if (matrix_type != 0 && matrix_type != 1)
        throw std::invalid_argument("matrix_type is not 0 or 1");

    for (int64_t m = 0; m < size; ++m) {
        for (int64_t n = 0; n < size; ++n) {
            data[m][n] = sequence[m + n] * sequence[m - n];
        }
    }
}


//Calculates determinant
template<typename F>
F Matrix<F>::LazyDeterminant() const {
    std::vector<size_t> perm(data.size());
    for (size_t i = 0; i < perm.size(); ++i) {
        perm[i] = i;
    }

    BigInt perm_num = factorial(BigInt((long long)data.size()));
    F pos_det = F(0);
    F neg_det = F(0);
    for (BigInt i = BigInt(0); i < perm_num; ++i) {
        size_t inv_cnt = 0;
        for (size_t u = 0; u < perm.size(); ++u)
            for (size_t j = u + 1; j < perm.size(); ++j)
                if (perm[u] > perm[j])
                    ++inv_cnt;

        F mul = F(1);
        for (size_t u = 0; u < data.size(); ++u) {
            mul = mul * data[u][perm[u]];
        }

        if (inv_cnt % 2 == 0)
            pos_det = pos_det + mul;
        else
            neg_det = neg_det + mul;
        std::next_permutation(perm.begin(), perm.end());
    }
    return pos_det - neg_det;
}

#define row std::vector<F>

// Function for vector subtraction
template<typename F>
row& subtract_row(row& lhs, const row& rhs, const F& coef, const size_t pos = 0) {
    if (lhs.size() != rhs.size())
        throw;
    //throw std::exception("Subtracting rows of different sizes");

    for (size_t i = pos; i < lhs.size(); ++i) {
	lhs[i] -= coef * rhs[i];
    }
    return lhs;
}

// Fuction for comparing a vector with zero vector
template<typename F>
bool non_zero_row(const row& r) {
    for (size_t i = 0; i < r.size(); ++i)
        if (r[i] != 0)
	    return true;
    return false;
}


template<typename F>
size_t Matrix<F>::GaussRank() const {
    size_t matrix_size = data.size();
    std::vector<row> data_cpy = data;
    size_t search_from = 0;
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = search_from; j < matrix_size; ++j) {
	    if (data_cpy[j][i] != 0) {
	        std::swap(data_cpy[search_from], data_cpy[j]);
		break;
	    }
	}

	if (data_cpy[search_from][i] != 0) {
	    for (size_t j = search_from + 1; j < matrix_size; ++j) {
	        const F coef = data_cpy[j][i] / data_cpy[search_from][i];
		subtract_row(data_cpy[j], data_cpy[search_from], coef, i);
	    }
	    ++search_from;
	}
    }

    size_t rank = 0;
    for (size_t i = 0; i < matrix_size; ++i) {
        if (non_zero_row(data_cpy[i])) {
	    ++rank;
	}
    }
    return rank;
}

template<typename F>
std::ostream& operator << (std::ostream& out, Matrix<F>& m) {
    for (size_t i = 0; i < m.data.size(); ++i) {
	for (auto& val : m.data[i]) {
            out << val << '\t';
	}
	out << '\n' << '\n';
    }
    return out;
}
