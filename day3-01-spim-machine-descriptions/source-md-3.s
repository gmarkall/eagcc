	.text
	.align 2
	.globl main
main:
	sw 	$ra, 0($sp)
	sw 	$sp, -4($sp)
	sw 	$fp, -8($sp)
	move 	$fp,$sp
	addi 	$sp, $fp, -36
	lw 	$a0, -12($fp)
	move 	$v0,$zero
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	add 	$v0, $v0, $a0
	move 	$sp,$fp
	lw 	$fp, -8($sp)
	lw 	$ra, 0($sp)
	jr 	$ra
