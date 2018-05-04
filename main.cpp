#include <iostream>
#include "u256.h"

using namespace std;

int main()
{
    cout << "u256 tests: \n\n" << endl;

    u256 A(256);
    u256 B(15);
    u256 C, D;

    cout << "\nA = "; A.print();
    cout << "\nB = "; B.print();

    A.division(B,C,D);
    cout << "\n C = A / B";
    cout << "\n D = A % B\n";
    cout << "\nC = "; C.print();
    cout << "\nD = "; D.print();

    return 0;
}
