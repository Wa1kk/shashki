#include <stdlib.h>
#include <string.h>
#include "objects.h"
#include "eval.h"
#include "symbols.h"
#include "parser.h"

extern object_t *t;

/** 
 * Сложение аргументов (+ 1 2 3)
 *
 * @param list - список чисел (1 2 3)
 *
 * @return сумму
 */
object_t add(object_t list)
{
    int num = 0;
    if (list == NULLOBJ) {
	    error("add: no arguments\n");
	    return ERROR;
    }
    while (list != NULLOBJ) {
	    object_t first = FIRST(list);
	    if (TYPE(first) == NUMBER || TYPE(first) == BIGNUMBER) {  
	        num += get_value(first);
	        list = TAIL(list);
	    }
	    else {
	        error("add: Not number\n");
	        return ERROR;
	    }
    }
    return new_number(num);
}

//Вычитание аргументов (- 1 2 3)

//@param list - список чисел (1 2 3)

//@return разность
object_t sub(object_t list)
{
   
    if (list == NULLOBJ) {
        error("sub: no arguments\n");
        return ERROR;
    }
    object_t first = FIRST(list);
    int num = get_value(FIRST(list));  
    list = TAIL(list);
    while (list != NULLOBJ) {
        object_t first = FIRST(list);
        if  (TYPE(first) == NUMBER || TYPE(first) == BIGNUMBER) {  
	        num -= get_value(first);
	        list = TAIL(list);
	}
	else {
            error("sub: Not number\n");
            return ERROR;
        }
    }
    return new_number(num);
}

//Умножение аргументов (* 1 2 3)

//@param list - список чисел (1 2 3)

//@return произведение
object_t mul(object_t list)
{
    if (list == NULLOBJ) {
	error("mul: no arguments\n");
	return ERROR;
    }
    object_t first = FIRST(list);
    int num = get_value(FIRST(list));
    list = TAIL(list);
    while(list != NULLOBJ){
	object_t first = FIRST(list);
	if(TYPE(first) == NUMBER || TYPE(first) == BIGNUMBER){
	    num *= get_value(first);
	    list = TAIL(list);
	}
	else{
	    error("mul: Not number\n");
	    return ERROR;
	}
    }
    return new_number(num);
}

/**
 * Деление (/ 8 2)
 * 
 * @param list - список чисел (8 2)
 *
 * @return результат от деления
 */
object_t int_div(object_t list){

    if (list == NULLOBJ) {
        error("div: no arguments\n");
        return ERROR;
    }
    if (TAIL(list) == NULLOBJ) {
        error("div: no divisor\n");
        return ERROR;
    }
    object_t first = FIRST(list);
    if (TYPE(first) != NUMBER && TYPE(first) != BIGNUMBER){
	 error("mul: Not number\n");
	 return ERROR;
    }
    object_t second = SECOND(list);
    if (TYPE(second) != NUMBER && TYPE(second) != BIGNUMBER){
	 error("mul: Not number\n");
	 return ERROR;
    }
    if (get_value(second) != 0) {
        int num = get_value(first) / get_value(second);
        return new_number(num);
    } else {
        error("div: divisor = 0 \n");
        return ERROR;
    }
}

/* Сравнение на больше (> 8 2) */

/* @param list - список чисел (8 2) */

/* @return результат от сравнения */

object_t gt(object_t list)
{
    if (list == NULLOBJ) {
        error(">: no arguments\n");
        return ERROR;
    }
    if (TAIL(list) == NULLOBJ) {
        error(">: one argument\n");
        return ERROR;
    }
    object_t first = FIRST(list);
    object_t second = SECOND(list);
    if (get_value(first) > get_value(second))
        return t;
    else 
        return NULLOBJ;
}

/* Сравнение на меньше (< 8 2) */

/* @param list - список чисел (8 2) */

/* @return результат от сравнения */
object_t less(object_t list)
{
    if (list == NULLOBJ) {
        error("<: no arguments\n");
        return ERROR;
    }
    if (TAIL(list) == NULLOBJ) {
        error("<: one argument\n");
        return ERROR;
    }
    object_t first = FIRST(list);
    object_t second = SECOND(list);
    if ( get_value(first) <  get_value(second))
        return t;
    else 
        return NULLOBJ;
}

/** 
 * Сравнение числовых аргументов (= 1 2)
 *
 * @param list - список чисел (1 2)
 *
 * @return T - если равно, иначе NIL
/*object_t *num_eq(object_t *list)
{
    object_t *n1 = FIRST(list);
    object_t *n2 = SECOND(list);
    if (n1->u.value == n2->u.value)
	return t;
    else
	return NULL;
}


/**
 * Функция сравнения объектов
 * возвращает 1 если значения объектов равны, иначе 0
/*int compare_obj(object_t *obj1, object_t *obj2)
{
    if (obj1 == NULL && obj2 == NULL)
	return 1;
    else if (obj1 == NULL || obj2 == NULL)
	return 0;
    if (obj1->type != obj2->type)
	return 0;
    else if (obj1->type == SYMBOL)
	return obj1->u.symbol == obj2->u.symbol;
    else if (obj1->type == STRING)
	return strcmp(obj1->u.str->data, obj2->u.str->data) == 0;
    else if (obj1->type == NUMBER)
	return obj1->u.value == obj2->u.value;
    else if (obj1->type == PAIR) {
	if (!compare_obj(FIRST(obj1), FIRST(obj2)))
	    return 0;
	else
	    return compare_obj(TAIL(obj1), TAIL(obj2));
    } else if (obj1->type == ARRAY) {
	if (obj1->u.arr->length != obj2->u.arr->length)
	    return 0;
	for (int i = 0; i < obj1->u.arr->length; i++)
	    if (!compare_obj(obj1->u.arr->data[i], obj2->u.arr->data[i]))
		return 0;	    
	return 1;
    }
}

/** 
 * Сравнение аргументов по значению (equal 1 2)
 *
 * @param list - список любых двух объектов (1 2)
 *
 * @return T - если равно, иначе NIL
 */
/*object_t *equal(object_t *list)
{
    if (list == NULL) {
        error("equal: no arguments\n");
        return ERROR;
    }
    object_t *obj1 = FIRST(list);
    if (TAIL(list) == NULL) {
        error("equal: no second argument\n");
        return ERROR;
    }
    object_t *obj2 = SECOND(list);
    if (TAIL(TAIL(list)) != NULL) {
        error("equal: too many arguments\n");
        return ERROR;
    }
    return compare_obj(obj1, obj2) ? t : NULL;
}

/** 
 * Побитовое И (& 1 2 3)
 *
 * @param list - список чисел (1 2 3)
 *
 * @return побитовое И
 */
object_t bitwise_and(object_t list)
{
    if (list == NULLOBJ) {
	error("bitwise_and: no arguments\n");
	return ERROR;
    }
    if (TYPE(FIRST(list)) != NUMBER) {
	error("bitwise_and: Not a number\n");
	return ERROR;
    }
    int num = get_value(FIRST(list));
    list = TAIL(list);
    while (list != NULLOBJ) {
	object_t first = FIRST(list);
	if (TYPE(first) == NUMBER) {  
	    num &= get_value(first);
	    list = TAIL(list);
	}
	else {
	    error("bitwise_and: Not number\n");
	    return ERROR;
	}
    }
    return new_number(num);
}

/** 
 * Побитовое ИЛИ (bitor 1 2 3)
 *
 * @param list - список чисел (1 2 3)
 *
 * @return побитовое ИЛИ
 */
object_t bitwise_or(object_t list)
{
    if (list == NULLOBJ) {
	error("bitwise_or: no arguments\n");
	return ERROR;
    }
    int num = get_value(FIRST(list));
    list = TAIL(list);
    while (list != NULLOBJ) {
	object_t first = FIRST(list);
	if (TYPE(first) == NUMBER) {  
	    num |= get_value(first);
	    list = TAIL(list);
	}
	else {
	    error("bitwise_or: Not number\n");
	    return ERROR;
	}
    }
    return new_number(num);
}

/**
 * Побитовый сдвиг влево (<< 8 2)
 * 
 * @param list - список (<Любое число> <Число бит>)
 *
 * @return результат сдвига

/*object_t *shift_left(object_t *list)
{
    if (list == NULL) {
        error("shift_left: no arguments\n");
        return ERROR;
    }
    if (TAIL(list) == NULL) {
        error("shift_left: no second param\n");
        return ERROR;
    }
    object_t *first = FIRST(list);
    object_t *second = SECOND(list);
    int num = first->u.value << second->u.value;
    return object_new(NUMBER, &num);
}

/**
 * Побитовый сдвиг вправо (>> 8 2)
 * 
 * @param list - список (<Любое число> <Число бит>)
 *
 * @return результат сдвига
 */

/*object_t *shift_right(object_t *list)
{
    if (list == NULL) {
        error("shift_right: no arguments\n");
        return ERROR;
    }
    if (TAIL(list) == NULL) {
        error("shift_right: no second param\n");
        return ERROR;
    }
    object_t *first = FIRST(list);
    object_t *second = SECOND(list);
    int num = first->u.value >> second->u.value;
    return object_new(NUMBER, &num);
}

/** 
 * Инициализация арифметических функций
 */
 

void init_arith()
{
    register_func("+", add);
    //register_func("-", sub);
    //register_func("*", mul);
    //register_func("=", num_eq);
    //register_func("EQUAL", equal);
    //register_func("/", int_div);
    //register_func("&", bitwise_and);
    //register_func("BITOR", bitwise_or);
    //register_func("<<", shift_left);
    //register_func(">>", shift_right);
    //register_func(">", gt);
    //register_func("<", less);
}
