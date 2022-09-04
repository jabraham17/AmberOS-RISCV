
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

void kinit() {
    uart_init();
}

void kmain() {
    // *uart = 'h';
    // *(uart) = 'e';


    // *(uart) = 'l';
    uart_printf("Hello world!\n");
    fire_mtimer();
    while(1) {
        char c = uart_getc();
        uart_printf("0x%hhx %c\n", c, c);
    }
    return;
}
