/*
 * Imię i nazwisko, numer indeksu: Jakub Szydło, 344760
 */
.data 
    max_ll: 
        .quad 9223372036854775807
    lmask: 
        .quad 0xff00ff00ff00ff00  
    rmask: 
        .quad 0x00ff00ff00ff00ff
    fmask: 
        .quad 0x8000800080008000
    fmask2: 
        .quad 0x0080008000800080

.text
    .globl  addsb
    .type addsb, @function

/*
 * W moim rozwiązaniu używam techniki: osobno dla parzystych i nieparzystych bajtów.
 * Zauważam, że (a^(a+b))&(b^(a+b)) sprawdza overflow lub underflow.
 * Traktuję każdy flow jako overflow, orując maskę do 0111111 i zerując pierwszy bit.
 * Jeśli underflow (pierwszy bit sumy zgaszony), to dodaję 1, co zmienia maskę overflow na underflow.
 */

addsb:  
    movq $0x00ff00ff00ff00ff, %r11 
    andn %rdi, %r11, %rdx 
    andn %rsi, %r11, %rcx 

    subq %rdx, %rdi 
    subq %rcx, %rsi

    leaq (%rdx, %rcx), %r8 
    xorq %r8, %rdx 
    xorq %r8, %rcx 
    andq %rdx, %rcx  
    andq fmask, %rcx  

    movq %rcx, %rdx 
    movq %rcx, %r11
    shrq $7, %rdx 
    imulq $127, %rdx 
    andn %r11, %r8, %r11 
    orq %rdx, %r8 
    andn %r8, %rcx, %r8
        
    andq lmask, %r8 

    leaq (%rdi, %rsi), %rcx 
    xorq %rcx, %rdi 
    xorq %rcx, %rsi 
    andq %rdi, %rsi  
    andq fmask2, %rsi  
    movq %rsi, %rdi 
    movq %rsi, %r10
    shrq $7, %rdi   
    imulq $127, %rdi 
    andn %r10, %rcx, %r10 
    orq %rdi, %rcx  
    andn %rcx, %rsi, %rcx 
        
    addq %r11, %r10
    shrq $7, %r10  
    andq rmask, %rcx  

    leaq (%r8, %rcx), %rax  
    addq %r10, %rax
    ret

.size addsb, .-addsb

