/*
 * Imię i nazwisko, numer indeksu: Jakub Szydło, 344760
 */
.data 
    mask1: 
        .quad 0xaaaaaaaaaaaaaaaa

.text
    .globl  bitrev
    .type bitrev, @function

/*
 * W moim rozwiązaniu używam techniki "dziel i zwyciężaj", zamieniając kolejno parami 
 * bloki długości 1, 2, 4, 8, 16 i 32. Ostatni blok (zamiana parami bitów z dwóch bloków po 32) 
 * optymalizuję operacją ror, co pozwala zmieścić się w limicie 32 operacji.
 */

bitrev:
    movq mask1, %r10
    movq $0xcccccccccccccccc, %rcx 
    movq $0xf0f0f0f0f0f0f0f0, %r8 
    movq $0xff00ff00ff00ff00, %r9 

    andq %rdi, %r10 
    subq %r10, %rdi
    shrq $1, %r10 
    shlq $1, %rdi 
    orq %r10, %rdi
    
    andq %rdi, %rcx 
    subq %rcx, %rdi
    shrq $2, %rcx 
    shlq $2, %rdi 
    orq %rcx, %rdi

    andq %rdi, %r8 
    subq %r8, %rdi
    shrq $4, %r8 
    shlq $4, %rdi 
    orq %r8, %rdi

    movq %rdi, %rcx
    movq %rdi, %rax
    rorq $32, %rcx
    ror $8, %cx 
    rorl $16, %ecx 
    ror $8, %cx
    ror $8, %ax
    rorl $16, %eax
    ror $8, %ax  
    rorq $32, %rax
    orq %rcx, %rax
    
    ret  

.size bitrev, .-bitrev

