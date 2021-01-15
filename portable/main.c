/**
 * @file   main.c
 * @author alex <alex@alex-Inspiron-N5040>
 * @date   Mon Oct 19 13:44:56 2020
 * 
 * @brief  Главный модуль ядра
 * 
 * 
 */

#include <x86/console.h>
#include <portable/libc.h>
#include <portable/mem.h>
#include <x86/idt.h>
#include <portable/timer.h>
#include <x86/irq.h>
#include <portable/keyboard.h>
#include <x86/mouse.h>
#include <x86/gdt.h>
#include <portable/proc.h>
#include <x86/cmos.h>
#include <portable/device.h>
#include <portable/file.h>
#include <portable/syscall.h>

extern void test_syscall();

/** 
 * Точка входа в ядро
 * 
 */
void kmain(void)
{
  init_memory();
  init_timer(10);
  init_devices();
  initProcesses();
  console_clear();
  init_interrupts();
  init_keyboard();
  init_disk();
  init_files();
  int descriptor = open("file.txt");
  kprint("open file %i\n", descriptor);
  //kprint(intToStr(get_phys_mem_size()));
  // int a = 1 / 0;
 
  // for(int i = 16; i<=22;i++)
  // {
  // test_mem(i);
  // }
  
  //test_syscall();
  

  // if (mouse_check() == 0xAA) {
  //kprint("Mouse detected\n");
  //} else {
  // kprint("No mouse\n");
  // } 
  // запуск процесса init

  /*
  Входные условия: id файла меньше 0.
  Правильный класс эквивалентности: ошибка ERROR_INVALID_PARAMETERS.
  Неправильный класс эквивалентности: возвращается 0.

  Входные условия: id файла больше NUM_FILES.
  Правильный класс эквивалентности: ошибка ERROR_INVALID_PARAMETERS.
  Неправильный класс эквивалентности: возвращается 0.

  Входные условия: по id не открыт никакой файл.
  Правильный класс эквивалентности: ошибка ERROR_INVALID_PARAMETERS.
  Неправильный класс эквивалентности: возвращается 0.

  Входные условия: id корректен, файл открыт.
  Правильный класс эквивалентности: возвращается 0, файлу присваиваются новые атрибуты.
  Неправильный класс эквивалентности: ошибка ERROR_INVALID_PARAMETERS.

  Входные условия: id корректен, файл открыт, вызов через sys_call.
  Правильный класс эквивалентности: возвращается 0, файлу присваиваются новые атрибуты.
  Неправильный класс эквивалентности: ошибка ERROR_INVALID_PARAMETERS.
  */
  int res = set_attr(-88, ATTR_REGULAR);
  kprint("Test #1, expected: -4, actual: %d\n", res);

  res = set_attr(322, ATTR_REGULAR);
  kprint("Test #2, expected: -4, actual: %d\n", res);

  res = set_attr(228, ATTR_REGULAR);
  kprint("Test #3, expected: -4, actual: %d\n", res);

  res = set_attr(descriptor, ATTR_DEVICE);
  kprint("Test #4, expected: 0, actual: %d\n", res);
  kprint("Expected attributes: 3, actual attributes: %d\n", get_attr(descriptor));

  res = sys_call(5, descriptor, ATTR_DIRECTORY, 0);
  kprint("Test #5, expected: 0, actual: %d\n", res);
  kprint("Expected attributes: 2, actual attributes: %d\n", get_attr(descriptor));


  kprint("mem = %d\n", memory_size());
  while(1) {
    print_time();
  }
	    // процесс ядра
}
