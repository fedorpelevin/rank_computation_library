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

enum {
    SIZE = 40,
};

int main() {
    srand( time( 0 ) );

    SomosSequence<rat> s(5, std::vector<rat>({1, 1}), std::vector<rat>({1, 1, 1, 1, 1}));
    //DualSomosSequence<rat> s(6, s4, std::vector<rat>({1, 1, 1, 0, 0, 0}), std::vector<rat>({1, 1, 1, 1, 0, 0}));
    //SomosSequence<rat> s5(5, std::vector<rat>({1, 1}), std::vector<rat>({1, 1, 1, 1, 1}));
    
    //ShiftedSomosSequence<rat> s(s5, 2, 1);
    
    s.Print(-10, 30);
    
    s.ComputeRank(SIZE, 0);
}
