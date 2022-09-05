
// unsigned char * uart = (unsigned char *)0x10000000;
// // #define uart ((unsigned char *)0x10000000)
// void putchar(char c) {
//     // while(*(uart++))
//     //     ;
//     *uart = c;
//     return;
// }

// void print(const char* str) {
//     while(*str != '\0') {
//         putchar(*str);
//         str++;
//     }
//     return;
// }

#include "drivers/uart/uart.h"
#include "timer/mtimer.h"
#include "trap/trap.h"
// #include "custom_instruction/custom_instruction.h"

// runs in machine mode
// last thing it does is enable virtual memory
void kinit() {
    uart_init();
    trap_init();
    // custom_instruction_init();
}
// extern int func(int x);


// runs in supervisor mode
void kmain() {
    uart_printf("Hello world!\n");
    //      int a = func(30);
    // uart_printf("Hello world! %d\n", a);
    // mtimer_fire();
    while(1) {
        char c = uart_getc();
        uart_printf("0x%hhx %c\n", c, c);
    }
    return;
}
