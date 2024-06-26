// Lab 1 template file
.data
.global lowercase_string
lowercase_string:
    // Specify a string ending with '\0'
    .asciz "eCE 362 is awesome!"

.global login_name
login_name:
    .asciz "tkalaska"

.global puid
puid:
    .asciz "0032777971"

// Align to 4bytes boundary as we have a string above
.balign 4

.text

.global q2_1_example
q2_1_example:
    // Assembly example
    add x0, x0, x1 // now, x0 = x0 + x1
    add x2, x2, x3 // now, x2 = x2 + x3
    add x0, x0, x2 // finally, x0 = (x0 + x1) + (x2 + x3)
    ret


.global q2_2_delta
q2_2_delta:
    // Compute the discriminant of a quadratic
    // function: b^2 - 4ac
    // x0: a
    // x1: b
    // x2: c
    // Put result back in x0

    /* Enter your code after this comment */
    mov x3, #4
    mul x1,x1,x1 //x1 = x1*x1
    mul x0,x0,x3 //x = 4*x0
    mul x0,x0,x2
    sub x0,x1,x0

    /* Enter your code above this comment */
    ret


.global q2_3_dot_product
q2_3_dot_product:
    // Compute the dot product of two 2-D vectors
    // dot(A, B) = a1b1 + a2b2
    // x0: a1
    // x1: a2
    // x2: b1
    // x3: b2
    // Put result back in x0

    /* Enter your code after this comment */
    mul x0,x0,x2
    mul x1,x1,x3
    add x0,x0,x1

    /* Enter your code above this comment */
    ret

.global q3_1_MSB
q3_1_MSB:
    // Extract the MSB of the incoming
    // 64-bit word and store in register
    // x0

    /* Enter your code after this comment */
    mov x1,#255
    lsl x1,x1,#56
    and x0,x0,x1
    lsr x0,x0,#56

    /* Enter your code above this comment */
    ret

.global q3_1_LSB
q3_1_LSB:
    // Extract the LSB of the incoming
    // 64-bit word and store in register x0
    mov x1,#255
    and x0,x0,x1


    /* Enter your code after this comment */

    /* Enter your code above this comment */
    ret

.global q3_2_flag_set
q3_2_flag_set:
    // Set the flag of a 64-bit value to 1
    // value: x0
    // flag:  x1
    // Put result back in x0

    /* Enter your code after this comment */
    orr x0,x0,x1

    /* Enter your code above this comment */
    ret

.global q3_2_flag_reset
q3_2_flag_reset:
    // Set the flag of a 64-bit value to 0
    // value: x0
    // flag:  x1
    // Put result back in x0

    /* Enter your code after this comment */
    mvn x1,x1
    and x0,x0,x1

    /* Enter your code above this comment */
    ret

.global q3_2_flag_toggle
q3_2_flag_toggle:
    // Toggle the flag of a 64-bit value
    // value: x0
    // flag:  x1
    // Put result back in x0

    /* Enter your code after this comment */
     eor x0,x0,x1
    /* Enter your code above this comment */
    ret

.global q3_3_swap_byte
q3_3_swap_byte:
    // Swap the LSB and MSB of a 64-bit word

    /* Enter your code after this comment */
    mov x1,#255
    lsl x1,x1,#56
    and x2,x0,x1
    lsr x2,x0,#56
    lsr x1,x1,#56
    and x3,x0,x1
    lsl x3,x3,#56
    orr x2,x2,x3
    and x3,x1,x3
    and x0,x0,0x00FFFFFFFFFFFF00
    orr x0,x0,x2

    /* Enter your code above this comment */
    ret

.global q4_1_toupper
q4_1_toupper:
    // Take in an address of a lowercase letter and save its uppercase form
    // to that address

    /* Enter your code after this comment */
    ldrb w1, [x0]
    sub w1,w1,#32
    strb w1, [x0]



    /* Enter your code above this comment */
    ret

.global q4_2_swap
q4_2_swap:
    // Take two 64-bit integers addresses and swap the content

    /* Enter your code after this comment */
    ldr x2, [x0]
    ldr x3, [x1]
    str x3, [x0]
    str x2, [x1]

    /* Enter your code above this comment */
    ret

.global q4_3_cutter
q4_3_cutter:
    // Take two arguments, a C character string starting address and a cut position
    // Passed in x0 and x1 respectively
    // After the function return, the string will be cut to position in register x1
    // i.e. string "Hello World!" with cut position 5 will results in "Hello"

    /* Enter your code after this comment */
    add x2,x0,x1
    mov x1, #0
    strb w1, [x2]
    /* Enter your code above this comment */
    ret

.global q4_4_cvt_endian
q4_4_cvt_endian:
    // Take in an 64-bit integer and reverse its endianness

    /* Enter your code after this comment */
    ldr x1, [x0]
    rev64 x1,x1
    str x1, [x0]
    /* Enter your code above this comment */
    ret
