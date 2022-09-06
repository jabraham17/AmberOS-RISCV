
.section .text

.global halt
halt:
    wfi
    j halt
