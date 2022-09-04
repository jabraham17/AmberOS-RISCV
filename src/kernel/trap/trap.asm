.section .text


.macro save_gp i, basereg=x31
	sd	x\i\(), ((\i)*8)(\basereg)
.endm
.macro load_gp i, basereg=x31
	# ld	x\i, ((\i)*8)(\basereg)
.endm

.set AFTER_REGS, (8*32)


.global m_trap_vector
.align 4
m_trap_vector:

    # save value of x31
    csrrw x31, mscratch, x31
    # use x31 as TrapFrame ptr
    sd x0, 0(x31)
    sd x1, 8(x31)
    sd x2, 16(x31)
    sd x3, 24(x31)
    sd x4, 32(x31)
    sd x5, 40(x31)
    sd x6, 48(x31)
    sd x7, 56(x31)
    sd x8, 64(x31)
    sd x9, 72(x31)
    sd x10, 80(x31)
    sd x11, 88(x31)
    sd x12, 96(x31)
    sd x13, 104(x31)
    sd x14, 112(x31)
    sd x15, 120(x31)
    sd x16, 128(x31)
    sd x17, 136(x31)
    sd x18, 144(x31)
    sd x19, 152(x31)
    sd x20, 160(x31)
    sd x21, 168(x31)
    sd x22, 176(x31)
    sd x23, 184(x31)
    sd x24, 192(x31)
    sd x25, 200(x31)
    sd x26, 208(x31)
    sd x27, 216(x31)
    sd x28, 224(x31)
    sd x29, 232(x31)
    sd x30, 240(x31)
    # save original value of x31
    mv a0, x31
    csrr x31, mscratch
    sd x31, 248(a0)

    # restore trap frame to scratch
    csrw mscratch, a0

    # save other regs into trap frame at a0
    csrr t0, mepc
    sd t0, (AFTER_REGS)(a0)
    csrr t0, mtval
    sd t0, (AFTER_REGS+8)(a0)
    csrr t0, mcause
    sd t0, (AFTER_REGS+16)(a0)
    csrr t0, mstatus
    sd t0, (AFTER_REGS+24)(a0)
    csrr t0, mhartid
    sd t0, (AFTER_REGS+32)(a0)

    # trap to handler
    call trap_handler
    # a0 has next address
    csrw mepc, a0

    # get trap frame and restore
    csrr x31, mscratch
    ld x1, 8(x31)
    ld x2, 16(x31)
    ld x3, 24(x31)
    ld x4, 32(x31)
    ld x5, 40(x31)
    ld x6, 48(x31)
    ld x7, 56(x31)
    ld x8, 64(x31)
    ld x9, 72(x31)
    ld x10, 80(x31)
    ld x11, 88(x31)
    ld x12, 96(x31)
    ld x13, 104(x31)
    ld x14, 112(x31)
    ld x15, 120(x31)
    ld x16, 128(x31)
    ld x17, 136(x31)
    ld x18, 144(x31)
    ld x19, 152(x31)
    ld x20, 160(x31)
    ld x21, 168(x31)
    ld x22, 176(x31)
    ld x23, 184(x31)
    ld x24, 192(x31)
    ld x25, 200(x31)
    ld x26, 208(x31)
    ld x27, 216(x31)
    ld x28, 224(x31)
    ld x29, 232(x31)
    ld x30, 240(x31)
    ld x31, 248(x31)
    # will also restore x31 automagically
    mret

