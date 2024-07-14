/*
 * Imię i nazwisko, numer indeksu: Jakub Szydło, 344760
 */
.data 
    lmask: 
        .quad 0xf0f0f0f0f0f0f0f0
    rmask: 
        .quad 0x0f0f0f0f0f0f0f0f
    mask5: 
        .quad 0x2020202020202020
    mask6: 
        .quad 0x4040404040404040
    mask7: 
        .quad 0x8080808080808080
    one: 
        .quad 1

.text
    .globl  mod17
    .type mod17, @function

/*
 * W moim rozwiązaniu używam techniki: przepływnięcia.
 * Dodaję 4-bitowe maski z sumą 4 bitów w 4 sumy bitów, które sumuję do 2 bitów.
 * Potem sumuję je do ostatniego bitu, iterując po modulo.
 */

mod17:
    movq %rdi, %rax 
    shrq $1, %rdi
    leaq (%rdi, %rax), %rdi 
    andq lmask, %rdi

    shrq $4, %rax 
    addq %rax, %rdi 

    movq %rdi, %rax
    andq rmask, %rax 
    shrq $8, %rdi 
    addq %rdi, %rax

    movq %rax, %rdi 
    andq mask5, %rdi
    shrq $16, %rax
    addq %rax, %rdi

    movq %rdi, %rax
    andq mask6, %rax
    shrq $32, %rdi 
    addq %rdi, %rax

    movq %rax, %rdi 
    shrq $1, %rax 
    addq %rdi, %rax

    movq %rax, %rdi 
    shrq $2, %rdi 
    addq %rdi, %rax
    movq %rax, %rdi 
    shrq $4, %rax 
    addq %rax, %rdi

    movq %rdi, %rax 
    shrq $8, %rdi 
    addq %rdi, %rax
    movq %rax, %rdi 
    shrq $16, %rax
    addq %rax, %rdi

    movq %rdi, %rax 
    shrq $32, %rdi 
    addq %rdi, %rax

    movq mask7, %rdi 
    andq %rdi, %rax 
    movq one, %rdi 
    cmpq %rdi, %rax 
    sbbl %eax, %eax 
    xorq %eax, %edi 
    ret

.size mod17, .-mod17

