	.text
	.align 2
	.globl main
main:
	sw 	$ra, 0($sp)
	sw 	$sp, -4($sp)
	sw 	$fp, -8($sp)
	move 	$fp,$sp
	addi 	$sp, $fp, -36
	lw 	$v0, -12($fp)
	sll 	$v0, $v0, 2
	sw 	$v0, -8($fp)
	lw 	$a0, -8($fp)
	lw 	$v0, -12($fp)
	sub	$v0, $a0, $v0
	sw 	$v0, -12($fp)
	move 	$v0,$zero
	move 	$sp,$fp
	lw 	$fp, -8($sp)
	lw 	$ra, 0($sp)
	jr 	$ra
