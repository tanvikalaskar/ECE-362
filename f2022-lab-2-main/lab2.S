// Lab 2 template file
.data
.global lowercase_string
lowercase_string:
    // Specify a string ending with '\0'
    .asciz "ece 362 is awesome!"

.global login_name
login_name:
    .asciz "tkalaska"

.global puid
puid:
    .asciz "0032777971"

// Align to 4bytes boundary as we have a string above
.balign 4

.text
.global asm_strlen
asm_strlen:
    /* uint64_t asm_strlen(char *str)
     * Take in a pointer to a string and return
     * its length up to the null terminating
     * character `\0`
     **/

    /* Enter your code after this comment */
      ldr x1, [x0]  // *str = x0
      mov x2, #0 //length

      CBZ x1,#0
      b.eq _end  // make end to return 0

      while:
      cbz x0, #0x00
      b.eq while_end

      add x1,x1,#1
      add x2,x2,#1
      b while


       _end:
      mov x0,#0

      while_end:
      str x0, [x2]





    /* Enter your code above this comment */
    ret

.global asm_fib
asm_fib:
    /* void asm_fib(int *arr, uint64_t length)
     * Accept a pointer to an array of integer and
     * the length of the array, then generate fibonacci
     * series starting at `0` and store the result
     * back to the array `arr` at corresponding indices.
     **/

    /* Enter your code after this comment */

    /* Enter your code above this comment */
    ret

.global asm_toUppercase
asm_toUppercase:
    /* void asm_toUppercase(char *str)
     * loop through an entire string and only convert
     * the lowercase letter to uppercase, leaving the
     * rest of the string intact
     **/

    /* Enter your code after this comment */

    /* Enter your code above this comment */
    ret
