            .data
msg:        .asciz "*****Print Name*****\n"
msg1:       .asciz "Team 09\n"
msg2:       .asciz "Chen Li Wei\n"
msg3:       .asciz "Wong Yu Kai\n"
msg4:       .asciz "Lin Yi Xian\n"
msg5:       .asciz "*****End Print*****\n"

type_num:   .asciz  "%d"
type_str:   .asciz  "%s"
enter:      .asciz  "\n"
p:          .word  'p'
word:       .word  '\0'
sum:        .word 0
num1:       .word 0         @ int num1 = 0
num2:       .word 0         @ int num2 = 0
num3:       .word 0         @ int num3 = 0

str:        .asciz  "%s"
num:        .asciz  "%d  "
str0:       .asciz  "%d\n"
str1:       .asciz  "*****Input ID*****\n"
str2:       .asciz  "** Please Enter Member 1 ID : \n"
str3:       .asciz  "** Please Enter Member 2 ID : \n"
str4:       .asciz  "** Please Enter Member 3 ID : \n"
str5:       .asciz  "** Please Enter Command **\n"
str6:       .asciz  "*****Print Team Member ID and ID Summation*****\n"
str7:       .asciz  "ID Summation = %d\n"
str8:       .asciz  "*****End Print*****\n"

fun1:       .asciz  "Function1: Name\n\n"
fun2:       .asciz  "\n\nFunction2: ID\n\n"
fun3:       .asciz  "\n\nMAIN Function: \n\n"
all:        .asciz  "*****Print All*****\n"

            .text
            .global main

main:   stmfd   sp!,{lr}        @ push lr onto stack
        mov     r0,#0
        subs    r0,r0,#1


        ldrmi   r0,=fun1        @ load fun1 to r0
        bl      printf          @ print "Function1: Name\n"
        bl      name            @ branch to name function

        ldr     r0,[r1,r2]

        ldr     r0,=fun2        @ load fun2 to r0
        bl      printf          @ print "\nFunction2: ID\n"
        bl      id              @ branch to id function

        cmp     r9,r8           @ compare r0 ,r8
        bne     pass            @ if not equal, branch to pass

        ldr     r0,=fun3        @ load fun3 to r0
        bl      printf          @ print "\nMAIN Function: \n"

        ldr     r0,=all         @ load all to r0
        bl      printf          @ print "*****Print All*****\n"

        ldr     r0,=msg1        @ load msg1 to r0
        bl      printf          @ print "Team 09\n"


        ldr     r0,=num         @ load address of format string
        mov     r1,r4           @ load int variable
        bl      printf          @ print the variable
        ldr     r0,=msg2        @ load msg2 to r0
        bl      printf          @ print "Chen Li Wei\n"

        ldr     r0,=num         @ load address of format string
        mov     r1,r5           @ load int variable
        bl      printf          @ print the variable
        ldr     r0,=msg3        @ load msg3 to r0
        bl      printf          @ print "Wong Yu Kai\n"

        ldr     r0,=num         @ load address of format string
        mov     r1,r6           @ load int variable
        bl      printf          @ print the variable
        ldr     r0,=msg4        @ load msg4 to r0
        bl      printf          @ print "Lin Yi Xian\n"

        mov     r1,r7
        ldr     r0,=str7        @ load the address of format string
        bl      printf          @ print "ID Summation = %d\n"

        ldr     r0,=str8        @ load str8 to r0
        bl      printf          @ print "*****End Print*****\n"

pass:   ldmfd   sp!,{lr}        @ pop lr fron stack
        mov     pc,lr           @ return from main

