#include <iostream>
#include "u256.h"

using namespace std;

int main()
{
    cout << "u256 tests: \n\n" << endl;

    u256 A(257);
    u256 B(15);
    u256 C;

    cout << "\nA = "; A.print();
    cout << "\nB = "; B.print();

    C = A / B; //     257 / 15 = 17
    cout << "\nC = "; C.print();

    return 0;
}
