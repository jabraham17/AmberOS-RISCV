.section .text


.global enable_mtimer_interrupts_asm
enable_mtimer_interrupts_asm:
    csrr t0, mie
    andi t0, t0, ~(1<<7)
    csrw mie, t0
    ret

.global disable_mtimer_interrupts_asm
disable_mtimer_interrupts_asm:
    csrr t0, mie
    ori t0, t0, (1<<7)
    csrw mie, t0
    ret
