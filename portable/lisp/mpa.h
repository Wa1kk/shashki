#ifndef BIGNUM_H
#define BIGNUM_H

#define MAX_BIGNUM_SIZE 100
#define MAX_BIGNUMS 100

/// Структура большого числа
typedef struct bign
{
    int size; /// Число десятичных цифр числа
    int sign; /// Знак числа
    char data[MAX_BIGNUM_SIZE]; /// Цифры числа, начиная с младшей цифры
    int exponent;
    struct bign *next;
    int free;
} *bignum_t;

bignum_t new_bignum();
bignum_t new_bignum_from_str(const char* str);
void free_bignum(bignum_t o);
void print_bignum(bignum_t num);
int bignum_sum(bignum_t n1, bignum_t n2);
int bignum_sub(bignum_t n1, bignum_t n2);
int bignum_mult(bignum_t n1, bignum_t n2);
int bignum_compare(bignum_t n1, bignum_t n2);
int bignum_div(bignum_t n1, bignum_t n2);

#endif 
