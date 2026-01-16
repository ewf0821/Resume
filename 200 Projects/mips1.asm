    .data
prompt: .asciiz "Enter a number (1 - 20): "
errorMsg1: .asciiz "Number must be > 0, try again.\n"
errorMsg2: .asciiz "Number must be < 21, try again.\n"
resultMsg: .asciiz "The fibonacci value is: "

    .text
    .globl main

main:
    # Allocate space on the stack for variables
    sub $sp, $sp, 8
    
    # Initialize number to -1
    li $t0, -1
    sw $t0, 0($sp)  # Store number on the stack

input_loop:
    # Get user input
    li $v0, 4
    la $a0, prompt
    syscall
    
    li $v0, 5
    syscall
    sw $v0, 4($sp)  # Store user input on the stack

    # Check if the number is less than 1
    blt $v0, 1, print_error1

    # Check if the number is greater than 20
    bgt $v0, 20, print_error2

    # Calculate fibonacci value
    lw $a0, 4($sp)
    jal fib

    # Print the result
    li $v0, 4
    la $a0, resultMsg
    syscall
    
    li $v0, 1
    lw $a0, 4($sp)
    syscall

    # Clean up and exit
    add $sp, $sp, 8
    li $v0, 10
    syscall

print_error1:
    # Print error message for number less than 1
    li $v0, 4
    la $a0, errorMsg1
    syscall
    j input_loop

print_error2:
    # Print error message for number greater than 20
    li $v0, 4
    la $a0, errorMsg2
    syscall
    j input_loop

fib:
    # Function to calculate fibonacci value
    # Input: $a0 - n
    # Output: $v0 - fibonacci value

    # Base case: n < 2
    blt $a0, 2, base_case
    
    # Recursive case
    sub $sp, $sp, 8
    sub $a0, $a0, 2
    jal fib
    move $s0, $v0

    add $a0, $a0, 1
    jal fib
    
    # Add the results
    add $v0, $s0, $v0

    # Clean up stack frame and return
    add $sp, $sp, 8
    jr $ra

base_case:
    # Base case: n = 0 or n = 1
    move $v0, $a0
    jr $ra
