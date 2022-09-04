#ifndef _KERNEL_DRIVERS_UART_UART_H_
#define _KERNEL_DRIVERS_UART_UART_H_

#include <stdlib/types.h>

void uart_init();

void uart_putc(char ch);
void uart_puts(char* str);

char uart_getc();

void uart_printf(char* fmt, ...);

#endif
