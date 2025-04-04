# Code generated using github.com/Nanrech/bf-mips
.data
tape: .space 30000

.text
main:
  # Set Memory Pointer
  la $t0, tape

  # Zero out tape
  li $t1, 7500
  _clear_tape:
  sw $zero, 0($t0)
  addi $t0, $t0, 4
  addi $t1, $t1, -1
  bnez $t1, _clear_tape
  la $t0, tape

  addi $t1, $t1, 8 # +
  andi $t1, $t1, 0xff

  _BO0: # [
  beqz $t1, _BC0

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 4 # +
  andi $t1, $t1, 0xff

  _BO1: # [
  beqz $t1, _BC1

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 2 # +
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 3 # +
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 3 # +
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 1 # +
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, -4
  lbu $t1, 0($t0)

  addi $t1, $t1, -1 # -
  andi $t1, $t1, 0xff

  bnez $t1, _BO1 # ]
  _BC1:

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 1 # +
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 1 # +
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, -1 # -
  andi $t1, $t1, 0xff

  sb $t1, 0($t0) # >
  addi $t0, $t0, 2
  lbu $t1, 0($t0)

  addi $t1, $t1, 1 # +
  andi $t1, $t1, 0xff

  _BO2: # [
  beqz $t1, _BC2

  sb $t1, 0($t0) # >
  addi $t0, $t0, -1
  lbu $t1, 0($t0)

  bnez $t1, _BO2 # ]
  _BC2:

  sb $t1, 0($t0) # >
  addi $t0, $t0, -1
  lbu $t1, 0($t0)

  addi $t1, $t1, -1 # -
  andi $t1, $t1, 0xff

  bnez $t1, _BO0 # ]
  _BC0:

  sb $t1, 0($t0) # >
  addi $t0, $t0, 2
  lbu $t1, 0($t0)

  li $v0, 11 # .
  move $a0, $t1
  syscall

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, -3 # -
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  addi $t1, $t1, 7 # +
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  li $v0, 11 # .
  move $a0, $t1
  syscall

  addi $t1, $t1, 3 # +
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  sb $t1, 0($t0) # >
  addi $t0, $t0, 2
  lbu $t1, 0($t0)

  li $v0, 11 # .
  move $a0, $t1
  syscall

  sb $t1, 0($t0) # >
  addi $t0, $t0, -1
  lbu $t1, 0($t0)

  addi $t1, $t1, -1 # -
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  sb $t1, 0($t0) # >
  addi $t0, $t0, -1
  lbu $t1, 0($t0)

  li $v0, 11 # .
  move $a0, $t1
  syscall

  addi $t1, $t1, 3 # +
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  addi $t1, $t1, -6 # -
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  addi $t1, $t1, -8 # -
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  sb $t1, 0($t0) # >
  addi $t0, $t0, 2
  lbu $t1, 0($t0)

  addi $t1, $t1, 1 # +
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  sb $t1, 0($t0) # >
  addi $t0, $t0, 1
  lbu $t1, 0($t0)

  addi $t1, $t1, 2 # +
  andi $t1, $t1, 0xff

  li $v0, 11 # .
  move $a0, $t1
  syscall

  # Exit Syscall
  li $v0, 10
  syscall
