/*
 * Imię i nazwisko, numer indeksu: Jakub Szydło, 344760
 */
.text
    .globl  wbs
    .type wbs, @function

/*
 * W moim rozwiązaniu używam techniki: redukcji liczby 1 bitów.
 * Wykonuję kolejne operacje and i shr na 1 bitach, by na koniec sumować wartości.
 */

wbs:
    movq %rdi, %rax
    movq %rdi, %rcx
    shrq $1, %rcx
    andq $0x5555555555555555, %rcx
    subq %rcx, %rax

    movq %rax, %rcx
    andq $0x3333333333333333, %rax
    shrq $2, %rcx
    andq $0x3333333333333333, %rcx
    addq %rcx, %rax

    movq %rax, %rcx
    shrq $4, %rcx
    addq %rax, %rcx
    andq $0x0f0f0f0f0f0f0f0f, %rcx

    movq %rcx, %rax
    shrq $8, %rax
    addq %rax, %rcx
    movq %rcx, %rax
    shrq $16, %rax
    addq %rax, %rcx

    movq %rcx, %rax
    shrq $32, %rax
    addq %rax, %rcx
    andq $0x7f, %rcx
    movq %rcx, %rax

    ret

.size wbs, .-wbs

