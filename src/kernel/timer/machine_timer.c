#include <stdlib/types.h>


void clear_mtimer() {

    //unset MIE MTIE
    __asm__ (
        "csrr t0, mie\n\t"
        "andi t0, t0, ~(1<<7)\n\t"
        "csrw mie, t0\n\t"
    );
}
void fire_mtimer() {

    // read current mtime
    volatile uint64_t* mtime = (uint64_t*)0x0200bff8;
    volatile uint64_t* mtimecmp = (uint64_t*)0x02004000;

    uint64_t current_cycles = *mtime;
    // QEMU freq is 10000000 Hz, so timer is set for 1 second
    uint64_t fire_after = 10000000;
    *mtimecmp = current_cycles + fire_after;


    // set MIE MTIE
    __asm__ (
        "csrr t0, mie\n\t"
        "ori t0, t0, (1<<7)\n\t"
        "csrw mie, t0\n\t"
    );
}
