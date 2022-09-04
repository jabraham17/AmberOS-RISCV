#include <drivers/uart/uart.h>
#include <stdlib/types.h>

// 296 bytes
struct TrapFrame {
    // values to restore
    uint64_t regs[32];

    // information
    uint64_t mepc;
    uint64_t mtval;
    uint64_t mcause;
    uint64_t mstatus;
    uint64_t mhartid;
};

extern void halt();

uint64_t trap_handler(struct TrapFrame* trap) {
    uint64_t pc = trap->mepc;

    uart_printf(
        "TRAP: from HART=%d, PC=0x%x, CAUSE=0x%x\n",
        trap->mhartid,
        trap->mepc, trap->mcause);

    // async
    if((trap->mcause >> 63) & 1) {
        uint64_t cause = trap->mcause & 0xFF;
        switch(cause) {
            case 3: {
                uart_printf("Machine Software Interrupt\n");
                break;
            }
            case 7: {
                uart_printf("Machine Timer Interrupt\n");
                clear_mtimer();
                fire_mtimer();
                break;
            }
            case 11: {
                uart_printf("Machine External Interrupt\n");
                break;
            }
            default: {
                uart_printf("Unhandled async interrupt cause 0x%x\n", cause);
                halt();
            }
        }
    } else {
        uint64_t cause = trap->mcause & 0xFFF;
        switch(cause) {
            // sync
            case 2: {
                uart_printf("Illegal Instruction\n");
                halt();
            }
            case 3: {
                uart_printf("Debug Breakpoint\n");
                halt();
            }
            case 8: {
                uart_printf("ECALL User\n");
                pc += 4;
                break;
            }
            case 9: {
                uart_printf("ECALL Supervisor\n");
                pc += 4;
                break;
            }
            case 11: {
                uart_printf("ECALL Machine\n");
                pc += 4;
                break;
            }
            case 12: {
                uart_printf("PAGE FAULT\n");
                pc += 4;
                break;
            }
            default: {
                uart_printf("Unhandled sync interrupt cause 0x%x\n", cause);
                halt();
            }
        }
    }

    return pc;
}
