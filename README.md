# Brainfuck to MIPS assembly compiler
---

## Usage
`bfcm.exe <input file> <output file>` will take the contents of `<input file>`, compile them, and dump the output into `<output file>`.
I recommend using [MARS](https://dpetersanderson.github.io/) for testing the generated code.

## Commands
`$t0` serves as the pointer.
`$t1` holds the contents of the currently pointed at cell.

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

## Building
I have attached the makefile I used throughout development. Since it's just a single file, you could also build the project using `g++ main.cpp -o bfcm`.
