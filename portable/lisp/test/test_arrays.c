#include <stdio.h>
#include "test.h"
#include "objects.h"
#include "alloc.h"
#include "symbols.h"
#include "array.h"
#include "parser.h"

void error(char *str, ...)
{
  printf("%s", str);
}

/**
 * Проверка создания массивов:
 * Создаём массив из 10 элементов и проверяем, что все элементы являются NULLOBJ
*/
void test_make_array()
{
    printf("test_make_array: ");
    int length = 10;
    object_t list = new_pair(new_number(length), NULLOBJ);
    object_t arr = make_array(list);
    PRINT(list);
    PRINT(arr);
    ASSERT(TYPE(arr), ARRAY);
    for (int i = 0; i < length; i++)
        ASSERT(GET_ARRAY(arr)->data[i], NULLOBJ);
}

/**
 * Проверка присваивания значения массиву:
 * Создаём массив на 5 элементов и присваиваем разные типы объектов в 0, 2, 4 и 7 индексы
*/
void test_seta()
{
    printf("test_seta: ");
    int length = 5;
    int num1 = 1337;
    int num2 = 42;
    int num3 = 0;
    int num4 = 2;
    int num5 = 4;
    int num6 = 7;
    object_t obj1 = new_number(num1);
    object_t obj2 = NEW_SYMBOL("ABCDEF");
    object_t obj3 = NEW_STRING("qwerty");
    object_t obj4 = new_number(num2);
    object_t list = new_pair(new_number(length), NULLOBJ);
    object_t arr = make_array(list);
    object_t cmd1 = new_pair(arr, new_pair(new_number(num3), new_pair(obj1, NULLOBJ)));
    object_t cmd2 = new_pair(arr, new_pair(new_number(num4), new_pair(obj2, NULLOBJ)));
    object_t cmd3 = new_pair(arr, new_pair(new_number(num5), new_pair(obj3, NULLOBJ)));
    object_t cmd4 = new_pair(arr, new_pair(new_number(num6), new_pair(obj4, NULLOBJ)));
    //    object_t cmd5 = new_pair(arr, new_pair(new_number(num1), new_pair(obj4, new_pair(new_number(num4), &num1), NULLOBJ))));
    seta(cmd1);
    seta(cmd2);
    seta(cmd3);
    object_t o = seta(cmd4);
    ASSERT(GET_ARRAY(arr)->data[num3], obj1);
    ASSERT(GET_ARRAY(arr)->data[num4], obj2);
    ASSERT(GET_ARRAY(arr)->data[num5], obj3);
    ASSERT(o, ERROR);
    //    object_t o2 = seta(cmd5);
    //    ASSERT(o2, ERROR);
}

/**
 * Проверка присваивания значения объекту и NULL
*/
void test_seta_invalid_arguments() {
    printf("test_seta_invalid_arguments: ");

    int num = 42;
    object_t obj = new_number(num);
    object_t result = seta(new_pair(obj, NULLOBJ));
    ASSERT(result, ERROR);
    
    result = seta(NULLOBJ);
    ASSERT(result, ERROR);

}

/**
 * Проверка присваивания значения массиву неверной структуры
*/
void test_seta_not_array() {
    printf("test_seta_not_array: ");

    int num = 42;
    int index = 0;
    object_t obj = new_number(num);
    object_t value = new_number(num);
    object_t list = new_pair(obj, new_pair(new_number(index), new_pair(value, NULLOBJ)));

    object_t result = seta(list);
    ASSERT(result, ERROR);
}

/**
 * Тестирование чтени элемента массива
 * Создать массив на 3 элемента 
 * Присвоить во 2 ячейку число 4 
 * Проверить число во 2 ячейке (aref arr 2)
 * Проверить 0 элемент массива
 */
void test_aref()
{
    printf("test_aref: ");
    int length = 3;
    int num = 4;
    int idx = 2;
    object_t list = new_pair(new_number(length), NULLOBJ);
    object_t arr = make_array(list);
    object_t obj = new_number(num);
    GET_ARRAY(arr)->data[2] = obj;
    object_t elem = aref(new_pair(arr, new_pair(new_number(idx), NULLOBJ)));
    ASSERT(get_value(elem), num);
    idx = 0;
    elem = aref(new_pair(arr, new_pair(new_number(idx), NULLOBJ)));
    ASSERT(elem, NULLOBJ);
}

/**
 * Тестирование чтения элемента массива по неверному индексу
 * Индекс передается как параметр index
 */
void test_aref_invalid_index(int index)
{
    printf("test_aref_invalid_index: ");
    int length = 3;
    int num = 4;
    object_t list = new_pair(new_number(length), NULLOBJ);
    object_t arr = make_array(list);
    object_t obj = new_number(num);
    GET_ARRAY(arr)->data[2] = obj;

    object_t elem = aref(new_pair(arr, new_pair(new_number(index), NULLOBJ)));
    ASSERT(elem, ERROR);
}

/**
 * Тестирование обращения по индексу к объекту, не являющемуся массивом
 */
void test_aref_invalid_array()
{
    printf("test_aref_invalid_array: ");
    int idx = 2;
    object_t obj = new_number(idx);
    object_t elem = aref(new_pair(obj, new_pair(new_number(idx), NULLOBJ)));
    ASSERT(elem, ERROR);
}

/**
 * Тестирование чтения элемента массива без параметров
 */
void test_aref_no_args()
{
    printf("test_aref_no_args: ");
    object_t elem = aref(NULLOBJ);
    ASSERT(elem, ERROR);
}

/**
 * Тестирование чтения элемента массива с одним параметром (только массив без индекса)
 */
void test_aref_only_array()
{
    printf("test_aref_only_array: ");
    int length = 3;
    object_t list = new_pair(new_number(length), NULLOBJ);
    object_t elem = aref(list);    
    ASSERT(elem, ERROR);
}

/**
 * Тестирование чтения элемента массива по неверному типу индекса
 */
void test_aref_invalid_index_type()
{
    printf("test_aref_invalid_index_type: ");
    int length = 3;
    int num = 4;
    object_t list = new_pair(new_number(length), NULLOBJ);
    object_t arr = make_array(list);
    object_t obj = new_number(num);
    GET_ARRAY(arr)->data[2] = obj;

    object_t elem = aref(new_pair(arr, new_pair(NEW_OBJECT(PAIR, new_pair(NULLOBJ, NULLOBJ)), NULLOBJ)));
    ASSERT(elem, ERROR);
}

int main()
{
    printf("------------test_arrays---------\n");
    init_regions();
    init_objects();
    test_make_array();
    test_seta();
    test_seta_invalid_arguments();
    test_seta_not_array();
    test_aref();
    test_aref_invalid_index(10);
    test_aref_invalid_index(-1);
    test_aref_invalid_index_type();
    test_aref_no_args();
    test_aref_only_array();
    test_aref_invalid_array();
    return 0;
}
