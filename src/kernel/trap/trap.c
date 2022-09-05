#include "trap.h"
#include <drivers/uart/uart.h>
#include <error/error.h>
#include <timer/mtimer.h>

// there are 16 interrupts
TrapInterruptHandler interrupt_handlers[16];
// there are 64 exceptions
TrapExceptionHandler exception_handlers[64];

bool trap_register_interrupt(
    TrapInterruptHandler handler,
    uint64_t exception_code) {
    if(exception_code < 16) {
        interrupt_handlers[exception_code] = handler;
        return true;
    }
    return false;
}

bool trap_register_exception(
    TrapExceptionHandler handler,
    uint64_t exception_code) {
    if(exception_code < 64) {
        exception_handlers[exception_code] = handler;
        return true;
    }
    return false;
}

static void trap_interrupt_3(__attribute__((unused)) struct TrapFrame* trap) {
    uart_printf("Machine Software Interrupt\n");
}
static void trap_interrupt_7(__attribute__((unused)) struct TrapFrame* trap) {
    uart_printf("Machine Timer Interrupt\n");
    mtimer_clear();
}
static void trap_interrupt_11(__attribute__((unused)) struct TrapFrame* trap) {
    uart_printf("Machine External Interrupt\n");
}
static uint64_t trap_exception_2(struct TrapFrame* trap) {
    uart_printf("Illegal Instruction\n");
    halt();
    return trap->mepc;
}
static uint64_t trap_exception_3(struct TrapFrame* trap) {
    uart_printf("Debug Breakpoint\n");
    return trap->mepc + 4;
}
static uint64_t trap_exception_8(struct TrapFrame* trap) {
    uart_printf("ECALL User\n");
    halt();
    return trap->mepc + 4;
}
static uint64_t trap_exception_9(struct TrapFrame* trap) {
    uart_printf("ECALL Supervisor\n");
    halt();
    return trap->mepc + 4;
}
static uint64_t trap_exception_11(struct TrapFrame* trap) {
    uart_printf("ECALL Machine\n");
    halt();
    return trap->mepc + 4;
}
static uint64_t trap_exception_12(struct TrapFrame* trap) {
    uart_printf("PAGE FAULT\n");
    halt();
    return trap->mepc + 4;
}

// register default handlers
void trap_init() {
    trap_register_interrupt(trap_interrupt_3, 3);
    trap_register_interrupt(trap_interrupt_7, 7);
    trap_register_interrupt(trap_interrupt_11, 11);

    trap_register_exception(trap_exception_2, 2);
    trap_register_exception(trap_exception_3, 3);
    trap_register_exception(trap_exception_8, 8);
    trap_register_exception(trap_exception_9, 9);
    trap_register_exception(trap_exception_11, 11);
    trap_register_exception(trap_exception_12, 12);
}

uint64_t mtrap_handler(struct TrapFrame* trap) {
    uint64_t pc = trap->mepc;

    uart_printf(
        "TRAP: from HART=%d, PC=0x%x, CAUSE=0x%x\n",
        trap->mhartid,
        trap->mepc,
        trap->mcause);

    int interrupt = (trap->mcause >> 63) & 1;
    if(interrupt) {
        uint64_t cause = trap->mcause & 0xFF;
        if(interrupt_handlers[cause]) {
            interrupt_handlers[cause](trap);
        } else {
            uart_printf("Unhandled interrupt 0x%x\n", cause);
            halt();
        }
    } else {
        uint64_t cause = trap->mcause & 0xFFF;

        if(exception_handlers[cause]) {
            return exception_handlers[cause](trap);
        } else {
            uart_printf("Unhandled exception 0x%x\n", cause);
            halt();
        }
    }
    return pc;
}
