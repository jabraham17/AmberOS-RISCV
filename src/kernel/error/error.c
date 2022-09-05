#include "error.h"
#include <drivers/uart/uart.h>


void panic(char* msg) {
    uart_printf("KERNEL PANIC: %s\n", msg);
    halt();
}
