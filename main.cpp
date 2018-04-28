#include <iostream>
#include "u256.h"

using namespace std;

int main()
{
    cout << "u256 tests: \n\n" << endl;

    u256 A(10020009);
    u256 B(1002002);

    bool b = (A==B);
    if (b) cout << "true\n"; else cout << "false\n";

    u256 C;
    C = A * B;
    cout << "C = ";
    C.print();

    cout << "A = "; A.print(true);
    cout << "B = "; B.print(true);



    return 0;
}
