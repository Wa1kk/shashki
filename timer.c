/**
 * @file   timer.c
 * @author TSAG <tsag@kali.tsag.com>
 * @date   Mon Oct 26 09:04:54 2020
 * 
 * @brief Инициализация программируемого интервального таймера
 * 
 * 
 */

#include "types.h"


/** 
 * инициализация таймера с заданной частотой
 * 
 * @param frequency частота
 */
void init_timer(int frequency)
{
  int divisor; /* Делитель частоты */
  uchar low; /* Младший байт делителя */
  uchar high; /* Старший байт делителя */

  /* Рассчитываем делитель по частоте */
  divisor = 1193180/frequency;

  /* Задаем режим работы таймера */
  write_port(0x43, 0x36);

  /* Переводим делитель в байты */
  low = (uchar) (divisor & 0xFF);
  high = (uchar) ( (divisor >>8) & 0xFF);

  /* Отсылаем в канал 0 PIT */
  write_port(0x40, low);
  write_port(0x40, high);
}
