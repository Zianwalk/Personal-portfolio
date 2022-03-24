
        .data
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
str0:       .asciz  "%d\n"
str1:       .asciz  "*****Input ID*****\n"
str2:       .asciz  "** Please Enter Member 1 ID : \n"
str3:       .asciz  "** Please Enter Member 2 ID : \n"
str4:       .asciz  "** Please Enter Member 3 ID : \n"
str5:       .asciz  "** Please Enter Command **\n"
str6:       .asciz  "*****Print Team Member ID and ID Summation*****\n"
str7:       .asciz  "ID Summation = %d\n"
str8:       .asciz  "*****End Print*****\n"

        .text
        .global id

id:   stmfd   sp!,{lr}        @ push link register onto stack

        ldr     r0,=str1        @ load str1 to r0
        bl      printf          @ print "*****Input ID*****\n"

        ldr     r0,=str2        @ load str2 to r0
        bl      printf          @ print "** Please Enter Member 1 ID : \n"

        ldr     r0,=type_num    @ load address of format string
        ldr     r1,=num1        @ load address of int variable
        bl      scanf           @ call scanf( "%d", &num1 )
        ldr     r4,=num1        @ load id1 address to r4

        ldr     r0,=str3        @ load str3 to r0
        bl      printf          @ print "** Please Enter Member 2 ID : \n"



        ldr     r0,=type_num    @ load address of format string
        ldr     r1,=num2        @ load address of int variable
        bl      scanf           @ call scanf( "%d", &num2 )
        ldr     r5,=num2        @ load id2 address to r5

        ldr     r0,=str4        @ load str4 to r0
        bl      printf          @ print "** Please Enter Member 3 ID : \n"


        ldr     r0,=type_num    @ load address of format string
        ldr     r1,=num3        @ load address of int variable
        bl      scanf           @ call scanf( "%d", &num3 )
        ldr     r6,=num3        @ load id3 addess to r6

        ldr     r0,=str5        @ load str5 to r0
        bl      printf          @ print "** Please Enter Command **\n"


        ldr     r0,=type_str    @ load address of format string
        ldr     r1,=word        @ load address of string variable
        bl      scanf           @ call scanf( "%s", word )
        ldr     r0,=word        @ load word address to r0

        ldr     r8,=p           @ load p address to r8

        ldr     r0,[r0]         @ load string variable
        ldr     r8,[r8]         @ load string variable( r8 = 'p' )

        mov     r9,r0
        cmp     r0,r8           @ compare r0 ,r8
        bne     pass            @ if not equal, branch to pass

        ldr     r0,=str6        @ load str6 to r0
        bl      printf          @ print "*****Print Team Member ID and ID Summation*****\n"

        ldr     r0,=str0        @ load str0 to r0
        ldr     r1,[r4]         @ load int variable
        bl      printf          @ print

        ldr     r0,=str0        @ load str0 to r0
        ldr     r1,[r5]         @ load int variable
        bl      printf          @ print

        ldr     r0,=str0        @ load str0 to r0
        ldr     r1,[r6]         @ load int variable
        bl      printf          @ print

        ldr     r0,=enter       @ load the address of the format string
        bl      printf          @ print '\n'

        ldr     r4,[r4]         @ load int variable
        ldr     r5,[r5]         @ load int variable
        ldr     r6,[r6]         @ load int variable

        add     r1,r4,r5        @ r1 = r4 + r5
        add     r1,r1,r6        @ r1 = r1 + r6
        mov     r7,r1           @ get summation value to r7

        ldr     r0,=sum
        str     r7,[r0]
        ldr     r7,[r0]

        ldr     r0,=str7        @ load the address of format string
        bl      printf          @ print "ID Summation = %d\n"

        ldr     r0,=str8        @ load str8 to r0
        bl      printf          @ print "*****End Print*****\n"
pass:
        mov     r0,#0           @ load return value
        ldmfd   sp!,{lr}        @ pop link register from stack
        mov     pc,lr           @ return from main

