.section .text

# a0 is address of where to jump
.global switch_to_user
switch_to_user:

    # set SPP to 0
    csrr t0, sstatus
    andi t0, t0, ~(1<<8)
    csrw sstatus, t0

    csrw sepc, a0
    sret

# a0 is address of where to jump
.global switch_to_supervisor
switch_to_supervisor:
    # set MPP to 01
    csrr t0, sstatus
    andi t0, t0, (1<<8)
    csrw sstatus, t0

    csrw sepc, a0
    sret

# a0 is address of where to jump
.global switch_to_machine
switch_to_machine:
    # set MPP to 11
    csrr t0, mstatus
    li t1, (3<<11)
    or t0, t0, t1
    csrw mstatus, t0

    csrw mepc, a0
    mret

