
        .data
type_num:   .asciz  "%d"
str:        .word   0

msg:    .asciz "*****Print Name*****\n"
msg1:   .asciz "Team 09\n"
msg2:   .asciz "Chen Li Wei\n"
msg3:   .asciz "Wong Yu Kai\n"
msg4:   .asciz "Lin Yi Xian\n"
msg5:   .asciz "*****End Print*****\n"


        .text
        .global name

 name:  stmfd   sp!,{lr}        @ push lr onto stack

        mov     r1,#-1
        mov     r2,#0

        adcs    r0,r1,r2        @ for project ask
        blne    pass

do:     ldreq   r0,=msg         @ load msg to r0
        bl      printf          @ print "*****Print Name*****\n"

        ldreq   r0,=msg1        @ load msg1 to r0
        bl      printf          @ print "Team 09\n"

        ldreq   r0,=msg2        @ load msg2 to r0
        bl      printf          @ print "Chen Li Wei\n"

        ldreq   r0,=msg3        @ load msg3 to r0
        bl      printf          @ print "Wong Yu Kai\n"

        ldreq   r0,=msg4        @ load msg4 to r0
        bl      printf          @ print "Lin Yi Xian\n"

        ldreq   r0,=msg5        @ load msg5 to r0
        bl      printf          @ print "*****End Print*****\n"

pass:   ldmfd   sp!,{lr}        @ pop lr from stack
        mov     pc,lr           @ return from main

