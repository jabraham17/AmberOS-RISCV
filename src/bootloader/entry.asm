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


    # set mstatus
    # set MPP(11) to 11 for machine mode
    # set MPIE(7) to 1, matches MIE
    # set MIE(3) to 1 for interrupt enable
    li t0, (3 << 11) | (1 << 7) | (1 << 3)
    csrw mstatus, t0
    # set mtvec to be a trap handler
    la t0, m_trap_vector
    csrw mtvec, t0
    # init location for trap frame
    la t0, _trap_frame_addr
    csrw mscratch, t0


    # trap return to kinit
	la t0, kinit
	csrw mepc, t0
    la ra, 2f
    mret
2:

    # enable interrupts on mie
    # set MSIE(3) to 1 for Int Enable for software interrupts
    # set MTIE(7) to 1 for  Int Enable for Timers interrupts
    # set MEIE(11) to 1 for Int Enable for Machine interrupts
    li t0, (1 << 3) | (1 << 7) | (1 << 11)
    csrw mie, t0

    # set mstatus
    # set MPP(11) to 11 for machine mode
    # set MPIE(7) to 1, matches MIE
    # set MIE(3) to 1 for interrupt enable
    li t0, (3 << 11) | (1 << 7) | (1 << 3)
    csrw mstatus, t0
    # trap return to kmain
    la t0, kmain
	csrw mepc, t0
    la ra, 3f
    mret
3:

    # halt
    j halt

.section .text
.global halt
halt:
    wfi
    j halt

.global asm_trap_vector
asm_trap_vector:
    j halt
    mret

