

#ifndef _KERNEL_TRAP_TRAP_H_
#define _KERNEL_TRAP_TRAP_H_

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

typedef void (*TrapInterruptHandler)(struct TrapFrame*);
typedef uint64_t (*TrapExceptionHandler)(struct TrapFrame*);
bool trap_register_interrupt(TrapInterruptHandler handler, uint64_t exception_code);
bool trap_register_exception(TrapExceptionHandler handler, uint64_t exception_code);

// installs default handlers
void trap_init();

#endif
