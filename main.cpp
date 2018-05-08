#include <iostream>
#include "u256.h"

using namespace std;

int main()
{
    cout << "u256 tests: \n\n" << endl;

    u256 A(256);
    u256 B(15);
    u256 C, D;

    cu256 E;
    cout << ">" << E.from_std_string("0xff",16);

    cout << "\n\n";
    for ( int i = 255; i >= 0; i--){
        cout << " " <<  int(E[i]);
    }

    return 0;
}
