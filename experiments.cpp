#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include "sequence.h"
#include "tools/matrix.h"
#include "tools/numbers/rational.h"
#include "tools/numbers/complex.h"

#define rat Rational
#define comp Complex<rat> 

enum {
    SIZE = 15
};

int main() {
    srand( time( 0 ) );

    SomosSequence<comp> s4(4, std::vector<comp>({{1, 1}, {1, 1}}), std::vector<comp>({{1, 1}, {1, 1}, {1, 1}, {1, 1}}));
    DualSomosSequence<comp> s(4, s4, std::vector<comp>({{1, 1}, {1, 1}, {1, 1}, {1, 1}}), std::vector<comp>({{1, 1}, 0, {1, 1}, 0}));
    //SomosSequence<comp> s(9, std::vector<comp>({1, 1, 1, 1}), std::vector<comp>({1, 1, 1, 1, 1, 1, 1, 1, 1}));
    for (int64_t i = -10; i <= 20; ++i) {
        std::cout << "s_{" << i << "} = " << s[i] << '\n';
    }   
    
    std::cout << "Инициализирую матрицу " << SIZE << 'x' << SIZE << ":\n";
    Matrix<comp> M0(s, SIZE, 0);
    std::cout << "Вычисляю ранг матрицы M0...\n";
    //std::cout << M0 << '\n';
    std::cout << "Ранг матрицы равен\t" << M0.GaussRank() << '\n';
}
