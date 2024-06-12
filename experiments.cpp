#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include "sequence.h"
#include "tools/matrix.h"
#include "tools/numbers/rational.h"

#define rat Rational

enum {
    SIZE = 11
};

int main() {
    srand( time( 0 ) );

    SomosSequence<rat> s4(4, std::vector<rat>({1, 1}), std::vector<rat>({1, 1, 1, 1}));
    //NSomosSequence<BigInt> s(s4);
    DualSomosSequence<rat> s(4, s4, std::vector<rat>({1, 1}), std::vector<rat>({1, 0, 0, 0}));

    for (int64_t i = -10; i <= 20; ++i) {
        std::cout << "s_{" << i << "} = " << s[i] << '\n';
    }   
    
    std::cout << "Инициализирую матрицу " << SIZE << 'x' << SIZE << ":\n";
    Matrix<rat> M0(s, SIZE, 0);

    std::cout << "Введите размер миноров:\n";
    size_t size;
    std::cin >> size;
    size_t cnt = 1;
    while (true) {
        std::cout << "COMPUTE\tCOMPUTE\n";

        std::set<size_t> rows;
        std::vector<size_t> row;
        std::set<size_t> cols;
        std::vector<size_t> col;
        for (size_t i = 0; i < size; ++i) {
            int x = abs(rand() % SIZE);
            while (rows.find(x) != rows.end()) {
               x = abs(rand()) % SIZE;
            }
            rows.insert(x);
        }
        for (size_t i = 0; i < size; ++i) {
            int x = abs(rand()) % SIZE;
            while (cols.find(x) != cols.end()) {
               x = abs(rand()) % SIZE;
            }
            cols.insert(x);
        }

        for (const auto ind : rows) {
            row.push_back(ind);
        }
        for (const auto ind : cols) {
            col.push_back(ind);
        }

        Matrix<rat> m1(M0, row, col);
        const auto val = m1.LazyDeterminant();
        if (val != 0) {
            std::cout << "Найден невырожденный минор " << size << "x" << size << ":\n";
            std::cout << "DET: " << val << '\n';
            for (auto r : rows) {
                std::cout << r << ' ';
            }
            std::cout << '\n';
            for (auto c : cols) {
                std::cout << c << ' ';
            }
            std::cout << '\n';
            
            std::cout << "Матрица:\n";
            std::cout << m1;
        }
    }
}
