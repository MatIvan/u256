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

u256::~u256()
{

}

const unsigned char &u256::operator[]( int i) const
{
    return array[i];
}

u256 u256::operator+( const u256 &other ) const
{
    u256 result;
    unsigned int c=0;
    int len = std::max(length(), other.length())+1;

    for (int i = 0; i<len ; i++ ){
        c += array[i] + other[i];
        result.set(i, c % base );
        c /= base;
    }
    return result;
}

u256 u256::operator-( const u256 &other ) const
{
    u256 result;
    int c=0;
    int l=0;
    int len = std::max(length(), other.length())+1;
    for (int i = 0; i<len ; i++ ){
        l = array[i] - c - other[i];
        c = l<0 ? 1 : 0;
        result.set(i, base * c + l);
    }
    return result;
}

u256 &u256::operator=( const u256 &other )
{
    set( other );
    return *this;
}

u256 &u256::operator<<(int n)
{
    for(int i=array_size-1; i>=0 ;i--){
        if (i<n) array[i]=0;
        else     array[i]=array[i-n];
    }
    calculate_length();
    return *this;
}

u256 &u256::operator>>(int n)
{
    for(int i=0; i<array_size; i++){
        if (i>=array_size-n) array[i]=0;
        else array[i]=array[i+n];
    }
    calculate_length();
    return *this;
}

bool u256::operator==( const u256 &other ) const
{
    for(int i=0; i<array_size; i++){
        if (array[i]!=other[i]) return false;
    }
    return true;
}

bool u256::operator<(const u256 &other) const
{
    for( int i=array_size-1; i>=0; i-- ){
        if (array[i]!=other[i]) return ( array[i]<other[i] );
    }
    return false;
}

bool u256::operator<=(const u256 &other) const
{
    return ((*this < other) | (*this == other));
}

bool u256::operator>(const u256 &other) const
{
    return (other < *this);
}

bool u256::operator>=(const u256 &other) const
{
    return (other <= *this);
}

u256 u256::operator*( const u256 & other ) const
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
    return r;
}

u256 u256::operator/(const u256 &other) const
{
    u256 wh, re;
    division(other, wh, re );
    return wh;
}

u256 u256::operator%(const u256 &other) const
{
    u256 wh, re;
    division(other, wh, re );
    return re;
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
    for (int i=0; i<array_size; i++){
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

void u256::calculate_length()
{
    _length = array_size;
    while ( array[_length-1] == 0 && _length > 0 ){
        _length--;
    }
}

bool u256::division(const u256 &other, u256 &whole, u256 &remainder) const
{
    u256 r;
    if(other == r) return false; //division by zero

    u256 m,s;
    m = *this;
    s = other;

    if (m.length() > s.length()) {
        s << ( m.length() - s.length() );
    }

    for (;;){
        while ( m >= s ){
            m = m - s;
            r = r + 1;
        }
        if ( s.length() <= other.length() ) break;
        s >> 1;
        r << 1;
    }
    whole = r;
    remainder = m;
    return true;
}

bool u256::division(const u256 &other, u256 &whole, char &remainder) const
{
    u256 r(remainder);
    if (!division(other,whole,r)) return false;
    remainder = r[0];
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

cu256::cu256(unsigned int n)
    : u256( n )
{

}

cu256::~cu256()
{

}

bool cu256::from_std_string(const std::string &str, int Base )
{
    unsigned start;

    if (Base==16){
        if ( !check_hex( str ) ) return false;
        start = 2;
    }
    if (Base==10){
        if ( !check_dec( str ) ) return false;
        start = 0;
    }

    std::vector<int> res(1);
    unsigned i, j;
    for ( i = start ; i < str.size(); i++){

        for( j=0; j<res.size(); j++){
            res[j] *= Base;
        }

        int dig = std::stoi( std::string(1, str[i]), 0, Base );
        res.front() += dig;
        normalize( res );
    }

    clear();
    for ( i = 0 ; i < res.size(); i++ ){
        set(i, (unsigned char)(res[i]) );
    }

    return true;
}

std::string cu256::to_std_string(int Base)
{
    std::string res;
    if ( (Base<1)||(Base>16) ) return res;

    std::string chs = "0123456789abcdef";

    char ch=0;
    u256 n = *this;
    u256 m;

    while ( n > 0 ){
        n.division( Base, m, ch );
        n = m;
        res.insert( 0, chs.substr(ch,1) );
    }
    if (Base==16) res.insert(0,"0x");
    return res;
}

bool cu256::check_hex(const std::string &hex) const
{
    if ( hex.substr(0,2) != "0x" ) return false;
    for ( unsigned i=2; i<hex.size(); i++ ){
        if ( ( toupper(hex[i]<'A'))||(toupper(hex[i])>'F') )
            if ( (hex[i]<'0')||(hex[i]>'9') ) return false;
    }
    return true;
}

bool cu256::check_dec(const std::string &dec) const
{
    for ( unsigned i=0; i<dec.size(); i++ ){
        if ( (dec[i]<'0')||(dec[i]>'9') ) return false;
    }
    return true;
}

void cu256::normalize(std::vector<int> &V)
{
    int remainder{};
    for ( unsigned i = 0; i < V.size(); i++ ){
        V[i] += remainder;
        remainder = V[i] / base;
        V[i] %= base;
    }
    if( remainder ) V.push_back( remainder );
    if ( (unsigned)V.back() >= base ) normalize( V );
}
