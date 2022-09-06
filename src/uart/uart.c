#include "uart.h"
#include <stdlib/stdarg.h>
#include <stdlib/string.h>
#include <stdlib/types.h>

// =======
// QEMU emulates the NS16550A UART chipset
// define UART registers
// ======
// volatile byte* _UART = (byte*)0x10000000;
// DLAB in LCR=0
volatile byte* _RECEIVER_BUFFER_REG_RO = (byte*)0x10000000;
volatile byte* _TRANSMITTER_HOLDING_REG_WO = (byte*)0x10000000;
// DLAB in LCR=0
volatile byte* _INTERRUPT_ENABLE_REG = (byte*)0x10000001;

volatile byte* _INTERRUPT_ID_REG_RO = (byte*)0x10000002;
volatile byte* _FIFO_CONTROL_REG_WO = (byte*)0x10000002;

volatile byte* _LINE_CONTROL_REG = (byte*)0x10000003;
volatile byte* _MODEM_CONTROL_REG = (byte*)0x10000004;
volatile byte* _LINE_STATUS_REG = (byte*)0x10000005;
volatile byte* _MODEM_STATUS_REG = (byte*)0x10000006;
volatile byte* _SCRATCH_REG = (byte*)0x10000007;

// DLAB in LCR=1
volatile byte* _DIVISOR_LATCH_LS = (byte*)0x10000000;
volatile byte* _DIVISOR_LATCH_MS = (byte*)0x10000001;

void uart_init() {
    // set word length
    byte lcr = 0b11;
    *_LINE_CONTROL_REG = lcr;

    // enable fio
    *_FIFO_CONTROL_REG_WO = 0b1;

    // enable receiever interrupts
    // *_INTERRUPT_ENABLE_REG = 0b1;

    // in QEMU, this will do nothing
    // set the clock divisor
    // first enable DLAB
    // *_LINE_CONTROL_REG = lcr | 1 << 7;
    // // set divisors
    // word divisor = 592;
    // *_DIVISOR_LATCH_LS = (byte)(divisor & 0xff);
    // *_DIVISOR_LATCH_MS = (byte)(divisor >> 8);
    // // reset DLAB
    // *_LINE_CONTROL_REG = lcr;
}

void uart_putc(char ch) { *_TRANSMITTER_HOLDING_REG_WO = ch; }
void uart_puts(char* str) {
    while(*str)
        uart_putc(*str++);
}

char uart_getc() {
    while((*_LINE_STATUS_REG & 0x1) == 0) {
    }
    return *_RECEIVER_BUFFER_REG_RO;
}

char uart_printf_buffer[1024];
void uart_printf(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsprintf(uart_printf_buffer, fmt, args);
    va_end(args);
    uart_puts(uart_printf_buffer);
}
