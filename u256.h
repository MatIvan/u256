#ifndef U256_H
#define U256_H

#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////
/// The u256 class
/// Базовый класс для работы с целым числом в 256 байт
///

class u256
{
public:
    static const int array_size = 256;
    static const unsigned int base = 256;

    u256( unsigned int n = 0 );
    virtual ~u256();

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
    u256 operator%(const u256 &other) const;

    const unsigned char &operator[]( int i ) const;
    bool division(const u256 &other, u256 &whole, u256 &remainder) const;

    void clear();
    int  length() const;
    bool set( const u256 &other );
    bool set(int position, unsigned char value);

private:
    unsigned char array[array_size];
    int _length;

    void calculate_length();

};

///////////////////////////////////////////////////////////////////////////////////////
/// The сu256 class
/// Класс унаследованный от базового u256.
/// Добавлены функции конвертации большого числа в DEC, HEX и обратно в виде строк
///
class cu256 : public u256
{
public:
    cu256( unsigned int n = 0 );
    virtual ~cu256();

    bool fromHEX( const std::string &hex );

private:
    bool check_hex( const std::string &hex ) const;

};

#endif // U256_H
