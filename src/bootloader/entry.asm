.section .init

.global _start
_start:

    # halt all but hart 0
    csrr t0, mhartid
    bnez t0, halt

	# SATP gets 0, no mem address translation
	csrw satp, zero

    # set gp
    la gp, _global_pointer
	# set stack
	la sp, _stack_top

	# zero BSS
    la t5, _bss_start
	la t6, _bss_end
1:
    sd zero, (t5)
	addi t5, t5, 8
	bgeu t5, t6, 1b

    # set mtvec to be a trap handler
    la t0, mtrap_vector_asm
    csrw mtvec, t0
    call enable_machine_interrupts


    la a0, minit
    call switch_to_machine
2:
    # enable interrupts on sie
    # set MSIE(3) to 1 for Int Enable for software interrupts
    # set MTIE(7) to 1 for  Int Enable for Timers interrupts
    # set MEIE(11) to 1 for Int Enable for Machine interrupts
    li t0, (1 << 3) | (1 << 7) | (1 << 11)
    csrw mie, t0

    call disable_supervisor_interrupts_from_machine

    la a0, kmain
    # call switch_to_supervisor
    call switch_to_machine
3:

    # halt
    j halt
