
#include "custom_instruction.h"
#include <firmware/trap/trap.h>

static uint64_t custom_instruction_handler(struct TrapFrame* trap) {
    uint64_t instruction = *(uint64_t*)(trap->mepc);

    unsigned reg_mask = 0x1F;
    unsigned opcode_mask = 0x7F;
    unsigned f7_mask = 0x7F;
    unsigned f3_mask = 0x7;

    unsigned funct7 = (instruction >> 25) & f7_mask;
    unsigned rs2_addr = (instruction >> 20) & reg_mask;
    unsigned rs1_addr = (instruction >> 15) & reg_mask;
    unsigned funct3 = (instruction >> 12) & f3_mask;
    unsigned rd_addr = (instruction >> 7) & reg_mask;
    unsigned opcode = instruction & opcode_mask;

    switch(opcode) {
        case 0x0B:
            // can do 1 of 3 things,
            // can rewrite into a valid instruction
            // or rewrite into a jmp/call to a native instruction handler
            // or just emulate and go to the next instruction
            // trap->regs[rd_addr] = trap->regs[rs1_addr] *
            // trap->regs[rs2_addr];
            instruction &= ~0x7F;
            instruction |= 0b00110011;
            *(uint64_t*)(trap->mepc) = instruction;
            return trap->mepc;
            break;
        default: break;
    }
    return trap->mepc + 4;
}

void custom_instruction_init() {
    trap_register_exception(custom_instruction_handler, 2);
}
