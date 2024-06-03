// Lab 3 template file
.data

.global login_name
login_name:
    .asciz "tkalaska"

.global puid
puid:
    .asciz "0032777971"

.balign 4

.equ TEST_SORT,         0x1
.equ TEST_STRCONCAT,    0x2
.equ TEST_FIB,          0x4
.equ TEST_BSEARCH,      0x8
.equ TEST_ALL,          (TEST_SORT | TEST_STRCONCAT | TEST_FIB | TEST_BSEARCH)

// Replace the TEST_ALL with the tests you want to run
// OR expression also support like the TEST_ALL above
// i.e. replace the TEST_ALL below with TEST_SORT | TEST_STRCONCAT
//      will test on the sort and strconcat
.global test
test:
    .word TEST_ALL


// Align to 4bytes boundary as we have a string above
.balign 4

.text
.global asm_sort_int
asm_sort_int:

    /* void asm_sort_int(int64_t* arr, uint64_t n)
     * relies on `qsort` in C standard library to 
     * sort in ascending order
     **/

   sub sp, sp, #16
   str x0, [sp, #8] // x0 = *arr
   str x30, [sp]    // x30 = link register

   mov x2, #8
   ldr x3, =asm_cmp
   bl qsort

   ldr x30, [sp]
   ldr x0, [sp, #8]
   add sp, sp, #16

	// ldr x3, =asm_cmp



    /* Enter your code above this comment */
    ret

.global asm_cmp
asm_cmp:
    // int asm_cmp(const void * a, const void * b)
    // Compare function to int64_t
    // used for qsort
    /* Enter your code after this comment */
    ldr x2, [x0] // a
    ldr x3 , [x1] // b


    sub x2, x2,x3

    cmp x2,#0
    b.lt _then
    mov x0, #1
    ret
    _then:
    mov x0, #-1

    /* Enter your code above this comment */
    ret

.global asm_strconcat
asm_strconcat:
    /* char* asm_strconcat(char * str1, char * str2)
     * First assign memory space with `malloc`, 
     * concatenating `str1` and `str2`, 
     * and return the resulted string.
     **/
    /* Enter your code after this comment */
    sub sp, sp, #16
    str x30, [sp, #8]
    mov x19, x0 // str1 =x19
    bl strlen
    mov x21, x0 // str2 = x20 , n1 = x21

    mov x0,x1
    mov x20,x0
    bl strlen
    mov x22,x0 // x22= n2

    add x24,x21,x22

    mov x2, #1 //sizeof(char) = 1
    add x24,x24,#1 // size -> x24
    mov x0, x24
    bl malloc
    mov x23, x0 // x23= buff
    mov x1,x19
    mov x2,x21
    bl memcpy

    add x0,x21,x23
    mov x1,x20
    mov x2,x22
    bl memcpy

    sub x24,x24,#1
    mov x0,#0
    strb w0, [x23, x24 ]
    mov x0,x23

    ldr x30, [sp, #8]
    add sp, sp, #16




    /* Enter your code above this comment */
    ret

.global asm_fib
asm_fib:
    /* uint64_t asm_fib(uint64_t n)
     * accept an index term `n` and return 
     * the Fn fibonacci term (F0 = 0, F1 = 1)
     **/

    /* Enter your code after this comment */
     sub sp, sp, #16
     str x30, [sp, #8]
     str x19, [sp]
     sub sp, sp, #16
     str x20, [sp, #8]

     cmp x0, #2

     b.ge _else
     b end



     _else:

    mov x19,x0 // n
    sub x0, x0, #1 // n-1
    bl asm_fib
    mov x20,x0 // asm_fib(n-1)
    sub x19,x19, #2 // (n-2)
    mov x0,x19
    bl asm_fib
    add x0,x0,x20


    end:
    ldr x20, [sp, #8]
    add sp, sp, #16
    ldr x19, [sp]
    ldr x30, [sp, #8]
    add sp, sp, #16





    /* Enter your code above this comment */
    ret

.global asm_bsearch
asm_bsearch:
    /* int64_t asm_bsearch(int *arr, int key, 
                    int64_t start,
                    int64_t end)
     * Return the index of the element in the array
     * if the element does not exist, return -1 instead
     * arr: integer array to be searched
     * key: the element we want to search on
     * start: start index of subarray, inclusive
     * end: end index of subarray, inclusiveloop through an entire string and only convert
     **/

    /* Enter your code after this comment */
     sub sp, sp, #16
     str x30, [sp, #8]
     // x0 = arr , x1 = key , x2 = start, x3 = end

     cmp x2,x3
     b.le other
     mov x0, #-1
     b end1

     other:
     mov x19, x0  //arr
     mov x20 , x1 // key
     mov x21, x2 // start
     mov x22, x3 // end

     mov x9, #2
     add x23,x2,x3
     udiv x23, x23,x9


	 lsl x11, x23, #2
     ldr w11, [x0, x11]
     cmp w11, w1
     b.ge second

     add x2,x23,#1

     bl asm_bsearch
     b end1

     second:
     cmp x11,x1
     b.le else1
//     mov x0,x19
//     mov x1,x20
//     mov x2, x21
     sub x3, x23, #1
     bl asm_bsearch
     b end1

     else1:
     mov x0, x23
     b end1

    end1:
    ldr x30, [sp, #8]
    add sp, sp, #16

    /* Enter your code above this comment */
    ret
