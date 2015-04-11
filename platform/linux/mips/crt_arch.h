__asm__("\n\
.set push\n\
.set noreorder\n\
.global __start\n\
.global _start\n\
.type   __start, @function\n\
.type   _start, @function\n\
__start:\n\
_start:\n\
	subu    $fp, $fp, $fp \n\
	lui     $gp, %hi(_gp) \n\
	addi    $gp, %lo(_gp) \n\
	move $4, $sp \n\
	subu $sp, $sp, 16 \n\
	and $sp, $sp, -8 \n\
	addi $sp, $sp, -4*6 \n\
	lw $25, %call16(__cstart)($gp) \n\
	jalr $25 \n\
	nop \n\
.set pop");
