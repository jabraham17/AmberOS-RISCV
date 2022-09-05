
.section .text


# execute custom multiply
.global func
func:
     nop
    nop
    # add a0, a0, a1
    # add
    # 0b0000000 01010 01010 000 01010 0110011
    # 0b00000000 10100101 00000101 00110011
    # .byte 0x33
    # .byte 0x05
    # .byte 0xA5
    # .byte 0x00
    # custom
    # 0b0000000 01010 01010 000 01010 0001101
    # 0b00000000 10100101 00000101 00001101
    .byte 0x0B
    .byte 0x05
    .byte 0xA5
    .byte 0x00
    ret
