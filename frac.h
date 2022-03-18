#ifndef MATRIX_FRAC_H
#define MATRIX_FRAC_H

#include <iostream>
#include <string>
#include <cassert>

class frac {
private:
    long long num;
    long long den;

public:

    ///Возвращает числитель дроби
    inline long long get_num(void);
    ///Возвращает знаменатель дроби
    inline long long get_den(void);
    ///Устанавливает числитель дроби num
    inline void change_num(long long num);
    ///Устанавливает знаменатель дроби num
    inline void change_den(long long den);

    frac(long long num, long long den);
    frac(long long num);
    frac(void);

    ///Сокращает дробь
    void reduction(void);

    friend frac operator - (frac a);

    friend frac operator + (frac a, frac b);
    friend frac operator - (frac a, frac b);
    friend frac operator * (frac a, frac b);
    friend frac operator / (frac a, frac b);

    friend frac operator += (frac &a, frac b);
    friend frac operator -= (frac &a, frac b);
    friend frac operator *= (frac &a, frac b);
    friend frac operator /= (frac &a, frac b);

    friend std::ostream& operator << (std::ostream& out, frac a);
    friend std::istream& operator >> (std::istream& in, frac &a);
    friend bool operator == (frac a, frac b);
    friend bool operator != (frac a, frac b);
    friend bool operator > (frac a, frac b);
    friend bool operator < (frac a, frac b);
    friend bool operator >= (frac a, frac b);
    friend bool operator <= (frac a, frac b);

};

///Приводит дробь к общиму знаменателю
void common_den(frac& a, frac& b);
///Возвращает строку в которую записана дробь
std::string msg(frac fr);

extern const frac FRAC_NEG_ONE;
extern const frac FRAC_ONE;
extern const frac FRAC_ZERO;
#endif //MATRIX_FRAC_H
