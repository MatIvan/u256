#include "u256.h"

u256::u256(unsigned int n)
{
    clear();
    int i = 0;
    do{
        array[i]= n % base;
        n = n / base;
        i++;
    } while (n!=0);
    calculate_length();
}

const unsigned char &u256::operator[]( int i) const
{
    return array[i];
}

u256 &u256::operator+( const u256 &other )
{
    unsigned int c=0;
    for (int i = 0; i< std::max(length(), other.length())+1; i++ ){
        c += array[i] + other[i];
        array[i] = c % base;
        c /= base;
    }
    calculate_length();
    return *this;
}

u256 &u256::operator-(const u256 &other)
{
    int c=0;
    int l=0;
    for (int i = 0; i< std::max(length(), other.length())+1; i++ ){
        l = array[i] - c - other[i];
        c = l<0 ? 1 : 0;
        array[i] = base*c + l ;
        /* Без условия, но так медленнее (наверное).
         * l = base + array[i] - c - other[i];
         * array[i] = l % base;
         * c = 1 - l / base;
         */
    }
    calculate_length();
    return *this;
}

u256 &u256::operator=(const u256 &other)
{
    for (int i=0; i>array_size; i++){
        array[i] = other[i];
    }
    _length = other.length();
    return *this;
}

void u256::clear()
{
    for ( int i = 0; i < array_size; i++){
        array[i] = 0;
    }
    _length = 0;
}

int u256::length() const
{
    return _length;
}

void u256::calculate_length()
{
    _length = array_size;
    while ( array[_length-1] == 0 && _length > 0 ){
        _length--;
    }
}
