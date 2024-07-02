# Lista 9 ASK -- rozwiazania  
## Zadanie 1
generalnie robiłem to jakimiś losowymi metodami chcąć usunąć sekcję `note.gnu.property` 
i doszedłem metodą prób i błędów do tego, że 
```sh
gcc data.c  -S -fcf-protection=none -Og -o data_cand.s 
```  
działa dokładnie tak jak byśmy tego sobie życzyli 
Jest to flaga, która wyłącza mechanizmy ochrony kontrolnego przepływu dostępne w kompilatorze GCC. 

part 2: 
```cpp 
.globl foo
.data
.align 2
.type foo, @object
.size foo, 2
foo:
    .value 314
    .section .rodata
    .type abc, @object
    .size abc, 4
 abc:
    .string "abc"
    .globl bar
    .bss
    .align 8
    .type bar, @object
    .size bar, 8
 bar:
    .zero 8

    .globl array
    .bss
    .align 32
    .type array, @object
    .size array, 800
 array:
    .zero 800
    .globl some
    .data
    .align 32
    .type some, @object
    .size some, 38
 some:
    .quad weird
    .long -3
    .zero 4
    .quad abc
    .quad foo
    
```
**.globl symbol** -- makes the symbol visible to ld. If you define symbol in your partial program, its value is made available to other partial programs that are linked with it. Otherwise, symbol takes its attributes from a symbol of the same name from another file linked into the same program.   
**.data subsection** -- .data tells as to assemble the following statements onto the end of the data subsection numbered subsection (which is an absolute expression). If subsection is omitted, it defaults to zero.   

**.type symbol @xyz** -- This directive is used to set the type of a symbol.  
For example @function, @object  
**.size** -- This directive is used to set the size associated with a symbol.  
```S
.size name, expression 
```
**.value 314** - służy do zdefiniowania stałej wartości w kodzie assemblerowym 

**.bss** --  tells as to assemble the following statements onto the end of the bss section. For most ELF based targets an optional subsection expression (which must evaluate to a positive integer) can be provided. In this case the statements are appended to the end of the indicated bss subsection.  
**.align** -- Pad the location counter (in the current subsection) to a particular storage boundary. The first expression (which must be absolute) is the alignment required, as described below. If this expression is omitted then a default value of 0 is used, effectively disabling alignment requirements.
For example ‘.align 3’ advances the location counter until it is a multiple of 8. If the location counter is already a multiple of 8, no change is needed.   
**.zero size** -- This directive emits size 0-valued bytes. size must be an absolute expression. This directive is actually an alias for the ‘.skip’ directive so it can take an optional second argument of the value to store in the bytes instead of zero. Using ‘.zero’ in this way would be confusing however. 
**.quad** - typ 64 bitowy 

## Zadanie 2 
`start.s`
```c
text
.globl _start /* określenie symbolu*/ 
.type _start, @function
_start:
    pushq %rax
    movl $42, %edi
    call is_even /*referencja do symbolu*/
    movl %eax, %edi
    movl $60, %eax
    syscall
    popq %rdx
ret
.size _start, .-_start 
``` 
`text.s`
```c
 .text
 .globl is_odd /*definicja symbolu */ 
 .type is_odd, @function
 is_odd:
    testq %rdi, %rdi
    je .L2
    decq %rdi
    jmp is_even /*referencja*/  
 .L2:
    xorl %eax, %eax
    ret
    .size is_odd, .-is_odd
``` 
`even.s`
```c
 .text
 .globl is_even /*definicja symbolu */ 
 .type is_even, @function
 is_even:
    testq %rdi, %rdi
    je .L2
    decq %rdi
    jmp is_odd
 .L2:
    movl $1, %eax
    ret
    .size is_even, .-is_even
```

```sh
 objdump -d odd.o   

odd.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <is_odd>:
   0:	48 85 ff             	test   %rdi,%rdi
   3:	74 08                	je     d <is_odd+0xd>
   5:	48 ff cf             	dec    %rdi
   8:	e9 00 00 00 00       	jmp    d <is_odd+0xd>
   d:	31 c0                	xor    %eax,%eax
   f:	c3                   	ret    
               
``` 

output z start.map 
```c 
Discarded input sections

 .comment       0x0000000000000000       0x28 even.o
 .note.GNU-stack
                0x0000000000000000        0x0 even.o
 .comment       0x0000000000000000       0x28 odd.o
 .note.GNU-stack
                0x0000000000000000        0x0 odd.o
 .comment       0x0000000000000000       0x28 start.o
 .note.GNU-stack
                0x0000000000000000        0x0 start.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

                0x00000000004000e8                . = (0x400000 + SIZEOF_HEADERS)

.text           0x00000000004000e8       0x39
 *(.text .text.*)
 .text          0x00000000004000e8       0x13 even.o
                0x00000000004000e8                is_even
 .text          0x00000000004000fb       0x10 odd.o
                0x00000000004000fb                is_odd
 .text          0x000000000040010b       0x16 start.o
                0x000000000040010b                _start

.rodata
 *(.rodata .rodata.*)

.eh_frame       0x0000000000400128       0x60
 .eh_frame      0x0000000000400128       0x30 even.o
 .eh_frame      0x0000000000400158       0x18 odd.o
                                         0x30 (size before relaxing)
 .eh_frame      0x0000000000400170       0x18 start.o
                                         0x30 (size before relaxing)

.data           0x0000000000400188        0x0
 *(.data .data.*)
 .data          0x0000000000400188        0x0 even.o
 .data          0x0000000000400188        0x0 odd.o
 .data          0x0000000000400188        0x0 start.o

.bss            0x0000000000400188        0x0
 *(.bss .bss.*)
 .bss           0x0000000000400188        0x0 even.o
 .bss           0x0000000000400188        0x0 odd.o
 .bss           0x0000000000400188        0x0 start.o
 *(COMMON)

/DISCARD/
 *(.rela.*)
 *(.iplt .iplt.*)
 *(.igot .igot.*)
 *(.got .got.*)
 *(.comment)
 *(.note.gnu.property)
 *(.note.GNU-stack)
LOAD even.o
LOAD odd.o
LOAD start.o
OUTPUT(start elf64-x86-64)
```

## Zadanie 4 
0040 1d 7b

0040 8357

5783 4000
podmieniona treść `ropex.in.txt` to: 
```
00000000: dead c0de dead c0de dead c0de dead c0de  ................
00000010: dead c0de dead c0de dead c0de dead c0de  ................
00000020: dead c0de dead c0de dead c0de dead c0de  ................
00000030: dead c0de dead c0de baad f00d 0000 0000  ................
00000040: 93 17 40 40 0d f4 44 00 0000 0000 0000 0000  @.@@..D.........
00000050: 2f75 7372 2f62 696e 2f6e 7961 6e63 6174  /usr/bin/nyancat
00000060: 000a                                     ................
``` 

tłumaczenie z hex na bin: 
```sh
xxd -r ropex.in.txt > ropex.in
```
uruchamianie kodu w gdb: 
```sh
gdb ropex 
set args ropex.in 
break 19 
c -- wykonuje jedną operację w c 
si -- wykonuje jedną operację w assembly 
```  

aby umieć cofać: 
```sh
record full 
reverse-step  
```
break 15 
s
s
i jesteśmy w odpowiednim miejscu 




