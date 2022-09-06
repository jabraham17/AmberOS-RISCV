

#include "trap/trap.h"
#include <uart/uart.h>

void minit() {
    uart_init();
    trap_init();
}
