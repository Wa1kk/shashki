#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "objects.h"
#include "symbols.h"

void str_copy (char *str1, char *str2);
int compare_str(char *str1, char *str2);
unsigned int hash(char *str);

symbol_t s;

symbol_t *new_symbol(char *str)
{
    symbol_t *symbol = (symbol_t*)malloc(sizeof(symbol_t));
    memset(symbol, 0, sizeof(symbol_t));
    strcpy(symbol->str, str);
    return symbol;
}

void test_compare_str(char *str, char *str2, int res)
{
    printf("test_compare_str: ");
    ASSERT(res, compare_str(str, str2));
}

void test_find_symbol(char *str, char *expected_symbol)
{
    printf("test_find_symbol: ");
    symbol_t *result = find_symbol(str);
    ASSERT(strcmp(result->str, expected_symbol), 0);
}

/** 
 * Тестирование символов с обинаковым хеш значением
 */
void test_same_hash()
{
    printf("test_same_hash:");
    char str1[] = "PJ";
    char str2[] = "452";
    printf("%d\n", hash(str1));
    printf("%d\n", hash(str2));
    ASSERT((find_symbol(str1) != find_symbol(str2)), 1);
}

/**
 * Создать символ "f" с помощью find_symbol
 * Получить символ "f" из таблицы с помощью find_symbol_get
 * Проверить что созданный и полученный символы совпадают
 */
void test_check_symbol()
{
    printf("test_check_symbol: ");
    symbol_t *s1 = check_symbol("f");
    ASSERT(s1, NULL);
    symbol_t *s2 = find_symbol("f");
    symbol_t *s3 = check_symbol("f");
    ASSERT(s2, s3);
}

object_t *test(object_t *list)
{
    return NULL;
}

/**
 * зарегистрировать функцию и проверить указатель
 */
void test_register_func()
{
    s.next = NULL;
    printf("test_register_func: ");
    register_func("TEST", test);
    strcpy(find_symbol("TEST")->str,"TEST");
    ASSERT(find_symbol("TEST")->func, test); 
}

/** 
 * Тестирование символов с обинаковым хеш значением
 */
void test_same_hash_three_symbols()
{
    printf("test_same_hash_three_symbols:");
    char str1[] = "PJ";
    char str2[] = "452";
    char str3[] = "\x7\x0   ";
    printf("!!!!\n");
    for (int i = 0; i < 256; i++ ) {
	str3[0] = i;
	str3[1] = 0;
	printf("%c %d\n", i, hash(str3));
    }
    for (int i = 0; i < 256; i++ )
        for (int g = 0; g < 256; g++ )
	     {
	str3[0] = i;
	str3[1] = g;
	str3[2] = 0;
	printf("%d %x %s %d\n", hash(str3), g, str3, i);
    }
    
    printf("!!!!\n");
    str3[0]= 7;
    
    printf("%d\n", hash(str1));
    printf("%d\n", hash(str2));
    printf("%d\n", hash(str3));
    ASSERT(((find_symbol(str1) != find_symbol(str2)) || (find_symbol(str1) != find_symbol(str3)) || (find_symbol(str2) != find_symbol(str3))), 1);
}

int main()
{
    printf("--------------test symbols---------------------\n");
    test_compare_str("abc", "abc", 1);
    test_compare_str("abc", "abc1", 0);
    test_find_symbol("a", "a");
    test_find_symbol("ab", "ab");
    test_check_symbol();
    test_register_func();
    test_same_hash();
}
