#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "list.h" 

#define MAX_OBJECTS 50
#define MAX_PAIRS 50

// Индекс последнего объекта массива
int last_object = 0;
// Массив или хранилище объектов
object_t objects[MAX_OBJECTS];


// Индекс последней пары
int last_pair = 0;
// Массив или хранилище пар
object_t pairs[MAX_PAIRS];

//создать объект
// type - тип объекта
// data - указатель на данные
// Возвращает указатель на созданный объект
object_t *object_new(type_t type, void *data)
{
    object_t *new = &objects[last_object++];
    if (last_object == MAX_OBJECTS)
        return NULL;
    new->type = type;
    if (type == NUMBER)
        new->u.value = *(int *)data;
    else if (type == ATOM)
        // заполнить поле строки
        new->u.atom = find_atom((char *)data);
    else if (type == PAIR)
        new->u.pair = (pair_t *)data;   
    return new;
}



/** 
 * Создание нового обекта пары
 * 
 * @param left левый объект
 * @param right правый объект
 * 
 * @return указатель на объект пары
 */
object_t *new_pair(object_t *left, object_t *right)
{
  pair_t *pair = &pairs[last_pair++];
  if (last_pair == MAX_PAIRS)
    return NULL;
  pair->left = left;
  pair->right = right;  
  return object_new(PAIR, pair);
}
