#include <stdlib/types.h>


extern void enable_mtimer_interrupts_asm();
extern void disable_mtimer_interrupts_asm();

void mtimer_clear() {
    disable_mtimer_interrupts_asm();
}

void mtimer_fire() {

    // read current mtime
    volatile uint64_t* mtime = (uint64_t*)0x0200bff8;
    volatile uint64_t* mtimecmp = (uint64_t*)0x02004000;

    uint64_t current_cycles = *mtime;
    // QEMU freq is 10000000 Hz, so timer is set for 1 second
    uint64_t fire_after = 10000000;
    *mtimecmp = current_cycles + fire_after;

    enable_mtimer_interrupts_asm();
}
