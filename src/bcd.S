.section .text.bcd_to_bin
.global bcd_to_bin
.type bcd_to_bin, @function
       
bcd_to_bin:
        mov     r16, r24
        andi    r24, 0x0F

1:      subi    r16, 10
        brcs    2f
        subi    r24, -10
        rjmp    1b

2:      ret

