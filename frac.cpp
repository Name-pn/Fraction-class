#include "frac.h"

const frac FRAC_NEG_ONE(-1, 1);
const frac FRAC_ONE(1, 1);
const frac FRAC_ZERO(0, 1);

//Возвращает наибольшее общее кратное двух чисел a и b
long long gcd(long long a, long long b) {
    if (a < 0)
        return gcd(-a, b);
    while (a * b != 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return(a + b);
}

//Возвращает наименьшее общее кратное двух чисел a и b
long long scm(long long a, long long b) {
    long long k = gcd(a, b);
    return ((a * b) / k);
}

inline long long frac::get_num(void) {
    return(num);
}

inline long long frac::get_den(void) {
    return(den);
}

inline void frac::change_num(long long num) {
    this->num = num;
}

inline void frac::change_den(long long den) {
    this->den = den;
}

void common_den(frac& a, frac& b) {
    long long k = scm(a.get_den(), b.get_den());
    long long t = k / a.get_den();
    a.change_num(t * a.get_num());
    t = k / b.get_den();
    b.change_num(t * b.get_num());
    a.change_den(k);
    b.change_den(k);
}

frac::frac(long long num, long long den) {
    this->num = num;
    this->den = den;
    assert(den != 0);
    if (den < 0 && num < 0) {
        den *= -1;
        num *= -1;
    }
    else if (den < 0 && num >= 0) {
        den *= -1;
        num *= -1;
    }
}

frac::frac(long long num) {
    this->num = num;
    this->den = 1;
}

frac::frac(void) {
    num = 0;
    den = 0;
}

frac operator - (frac a) {
    return a * FRAC_NEG_ONE;
}

frac operator + (frac a, frac b) {
    common_den(a, b);
    frac c(a.num + b.num, a.den);
    return (c);
}

frac operator - (frac a, frac b) {
    b.num *= -1;
    frac c = a + b;
    return (c);
}

frac operator * (frac a, frac b) {
    frac c(a.num * b.num, a.den * b.den);
    c.reduction();
    return (c);
}

frac operator / (frac a, frac b) {
    frac c(abs(a.num * b.den), abs(a.den * b.num));
    int sign = (a.get_num() < 0) + (b.get_num() < 0);
    if (sign % 2 == 1)
        c = c * FRAC_NEG_ONE;
    c.reduction();
    return (c);
}

frac operator += (frac &a, frac b) {
    return a + b;
}

frac operator -= (frac &a, frac b) {
    return  a - b;
}

frac operator *= (frac &a, frac b) {
    return  a * b;
}

frac operator /= (frac &a, frac b) {
    return  a / b;
}

std::string msg(frac a) {
    std::string msg;
    if (a.get_num() == 0 && a.get_den() == 0)
        return ("?");
    if (a.get_num() < 0) {
        msg = "-";
        a.change_num(-a.get_num());
    }
    if (a.get_num() % a.get_den() != 0)
        if (a.get_num() / a.get_den() != 0)
            msg += std::to_string(a.get_num() / a.get_den()) + "(" + std::to_string(a.get_num() % a.get_den()) + "/" + std::to_string(a.get_den()) + ")";
        else
            msg += std::to_string(a.get_num() % a.get_den()) + "/" + std::to_string(a.get_den());
    else
        msg += std::to_string(a.get_num() / a.get_den());
    return msg;
}

std::ostream& operator << (std::ostream& out, frac a) {
    return (std::cout << msg(a));
}

std::istream& operator >> (std::istream& in, frac &a) {
    std::string s;
    in >> s;
    size_t i = 0;
    long long num = 0;
    int sign = 1;
    if (s[i] == '-') {
        ++i;
        sign = -1;
    }
    while (s[i] <= '9' && s[i] >= '0' && i < s.length()) {
        num = num * 10 + s[i++] - '0';
    }
    a.num = num;
    if (i == s.length()) {
        a.den = 1;
    }
    else {
        if (s[i] == '/')
            ++i;
        else
            assert(s[i] != '/');
        num = 0;
        while (s[i] <= '9' && s[i] >= '0' && i < s.length()) {
            num = num * 10 + s[i++] - '0';
        }
        a.den = num == 0 ? 1 : num;
    }
    a.num *= sign;
    assert(a.den != 0);
    return in;
}

//Сокращает дробь
void frac::reduction(void) {
    long long k = gcd(num, den);
    num /= k;
    den /= k;
}

bool operator == (frac a, frac b) {
    a.reduction();
    b.reduction();
    return (a.num == b.num && a.den == b.den || a.num == b.num && a.num == 0);
}

bool operator != (frac a, frac b) {
    return (!(a == b));
}

bool operator > (frac a, frac b) {
    common_den(a, b);
    return(a.num > b.num);
}

bool operator < (frac a, frac b) {
    return(!(a > b) && a != b);
}

bool operator >= (frac a, frac b) {
    return(a > b || a == b);
}

bool operator <= (frac a, frac b) {
    return(a < b || a == b);
}
