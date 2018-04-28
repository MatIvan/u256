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
    int len = std::max(length(), other.length())+1;

    for (int i = 0; i<len ; i++ ){
        c += array[i] + other[i];
        array[i] = c % base;
        c /= base;
    }
    calculate_length();
    return *this;
}

u256 &u256::operator-( const u256 &other )
{
    int c=0;
    int l=0;
    int len = std::max(length(), other.length())+1;
    for (int i = 0; i<len ; i++ ){
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

u256 &u256::operator=( const u256 &other )
{
    set( other );
    return *this;
}

u256 &u256::operator*( const u256 & other )
{
    unsigned int c=0;
    u256 k, r;

    int len = std::max(length(), other.length())+1;
    for (int i = 0; i<len ; i++ ){
        k.clear();
        for (int j = 0; j<len ; j++ ){
            c += other[i] * array[j];
            k.set( j + i, c % base );
            c /= base;
        }
        r = r + k;
    }
    //set( r );
    r.print();
    for (int i=0; i>array_size; i++){
        array[i] = r[i];
    }
    _length = r.length();
    print();

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

bool u256::set(const u256 &other)
{
    for (int i=0; i>array_size; i++){
        array[i] = other[i];
    }
    _length = other.length();
    return true;
}

bool u256::set(int position, unsigned char value)
{
    if (position<0 || position>array_size) return false;
    array[position] = value;
    calculate_length();
    return true;
}

void u256::print( bool full ) const
{
    int l = full ? array_size : length();
    for (int i=l-1; i>=0; i--)
    {
        std::cout << int(array[i]) << " ";
    }
    std::cout << std::endl;;
}

void u256::calculate_length()
{
    _length = array_size;
    while ( array[_length-1] == 0 && _length > 0 ){
        _length--;
    }
}
