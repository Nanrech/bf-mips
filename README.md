# Brainfuck to MIPS assembly compiler
---
- `$t0` serves as the pointer.
- `$t1` holds the contents of the currently pointed at cell.

## Instructions
- `>`, `<`
```
sb $t1, 0($t0)
addi $t0, $t0, x
lbu $t1, 0($t0)
```
- `+`, `-`
```
addi $t1, $t1, x
andi $t1, $t1, 0xff
```
- `.`
```
li $v0, 11
move $a0, $t1
syscall
```
- `,`
```
li $v0, 12
syscall
move $t1, $v0
```
- `[`
```
_BOx:
beqz $t1, _BCx
```
- `]`
```
bnez $t1, _BOx
_BCx:
```
