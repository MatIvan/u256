#include <iostream>
#include "u256.h"

using namespace std;

int main()
{
    cout << "u256 tests: \n\n" << endl;

    u256 A(20053);
    u256 B(72);

    u256 C = A - B;

    for (int i=C.length()-1; i>=0; i--)
    {
        cout << int(C[i]) << " ";
    }

    return 0;
}
