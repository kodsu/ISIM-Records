/*
 * Imię i nazwisko, numer indeksu: Jakub Szydło, 344760
 */
.text
    .globl  clz
    .type clz, @function

/*
 * W moim rozwiązaniu używam techniki: dziel i zwyciężaj.
 * Program mógłby być bardziej czytelny, gdybym użył pętli, ale dodawałoby to więcej operacji.
 */

clz:
    xorq %rax, %rax 
    movq %rdi, %rsi 
    leaq 32(%rax), %r8 
    movq %rdi, %rcx 
    shrq $32, %rcx 
    movq $0xffffffff00000000, %r9 
    andq %r9, %rsi 
    cmove %r8, %rax 
    cmovne %rcx, %rdi 

    movq %rdi, %rsi 
    leaq 16(%rax), %r8 
    movq %rdi, %rcx 
    shrq $16, %rcx 
    movq $0xffff0000, %r9 
    andq %r9, %rsi 
    cmove %r8, %rax 
    cmovne %rcx, %rdi 

    movq %rdi, %rsi 
    leaq 8(%rax), %r8 
    movq %rdi, %rcx 
    shrq $8, %rcx 
    andq $0xff00, %rsi 
    cmove %r8, %rax 
    cmovne %rcx, %rdi 

    movq %rdi, %rsi 
    leaq 4(%rax), %r8 
    movq %rdi, %rcx 
    shrq $4, %rcx 
    andq $0xf0, %rsi 
    cmove %r8, %rax 
    cmovne %rcx, %rdi 

    movq %rdi, %rsi 
    leaq 2(%rax), %r8 
    movq %rdi, %rcx 
    shrq $2, %rcx 
    andq $0xc, %rsi 
    cmove %r8, %rax 
    cmovne %rcx, %rdi 

    movq %rdi, %rsi 
    leaq 1(%rax), %r8 
    movq %rdi, %rcx 
    shrq $1, %rcx 
    andq $0x2, %rsi 
    cmove %r8, %rax 
    cmovne %rcx, %rdi 

    leaq 1(%rax), %r8
    andq $1, %rdi 
    cmove %r8, %rax 
    ret

.size clz, .-clz

