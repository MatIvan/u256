#include <iostream>
#include "u256.h"

using namespace std;

int main()
{
    cout << "u256 tests: \n\n" << endl;

    u256 A(129);
    u256 B(15);

    u256 C;
    C = A * B;

    C.print();

    return 0;
}
