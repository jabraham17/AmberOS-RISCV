
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

#include <uart/uart.h>


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
