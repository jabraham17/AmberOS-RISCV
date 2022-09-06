
.section .text

.global disable_machine_interrupts
disable_machine_interrupts:
    # unset MIE and MPIE
    csrr t0, mstatus
    andi t0, t0, ~((1<<7) | (1<<3))
    csrw mstatus, t0
    ret

.global enable_machine_interrupts
enable_machine_interrupts:
    # set MIE and MPIE
    csrr t0, mstatus
    ori t0, t0, (1<<7) | (1<<3)
    csrw mstatus, t0
    ret

.global disable_supervisor_interrupts_from_machine
disable_supervisor_interrupts_from_machine:
    #  unset SIE and SPIE
    csrr t0, mstatus
    andi t0, t0, ~((1<<5) | (1<<1))
    csrw mstatus, t0
    ret

.global enable_supervisor_interrupts_from_machine
enable_supervisor_interrupts_from_machine:
    #  set SIE and SPIE
    csrr t0, mstatus
    ori t0, t0, (1<<5) | (1<<1)
    csrw mstatus, t0
    ret


.global disable_supervisor_interrupts
disable_supervisor_interrupts:
    #  unset SIE and SPIE
    csrr t0, sstatus
    andi t0, t0, ~((1<<5) | (1<<1))
    csrw sstatus, t0
    ret

.global enable_supervisor_interrupts
enable_supervisor_interrupts:
    #  set SIE and SPIE
    csrr t0, sstatus
    ori t0, t0, (1<<5) | (1<<1)
    csrw sstatus, t0
    ret
