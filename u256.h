#ifndef U256_H
#define U256_H

#include <iostream>

class u256
{
public:
    static const int array_size = 256;
    //static const unsigned int base = 256;
    static const unsigned int base = 10; //TODO поменять базу на 256

    u256( unsigned int n = 0 );

    u256 &operator=(const u256 &other);
    u256 &operator<<(int n);
    u256 &operator>>(int n);

    bool operator==(const u256 &other) const;
    bool operator< (const u256 &other) const;
    bool operator<=(const u256 &other) const;
    bool operator> (const u256 &other) const;
    bool operator>=(const u256 &other) const;

    u256 operator+(const u256 &other) const;
    u256 operator-(const u256 &other) const;
    u256 operator*(const u256 &other) const;
    u256 operator/(const u256 &other) const;

    const unsigned char &operator[]( int i ) const;

    void clear();
    int  length() const;
    bool set( const u256 &other );
    bool set(int position, unsigned char value);

    void print( bool full = false ) const;

private:
    unsigned char array[array_size];
    int _length;

    void calculate_length();

};

#endif // U256_H
