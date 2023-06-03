.text
.globl main

2000

lw $s0, 100($zero)

li $s1, 11
li $s2, 5
li $s3, 28
li $s4, 7
li $s5, 12

sub $t0, $s1, $s2
add $t1, $s3, $s4  #testing comments
add $t2, $t0, $t1
sub $s6, $t2, $s5

li $v0, 10
syscall
sll $t0, $t1, 10
move $t1, $t0   #comment
addi $s1, $s0, 10

la $t1, 100
la $s1, 3000
j 2000     #comment 2
bne $s0, $s1, 2000
.data
3000 .asciiz "\nEnter a positive integer: "

