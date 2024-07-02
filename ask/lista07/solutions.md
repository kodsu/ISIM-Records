
# Rozwiązania - lista 7

## Zadanie 3 
```c 
 long A[R][S][T];

 long store_elem(long i, long j,
 long k, long *dest)
 {
 *dest = A[i][j][k];
 return sizeof(A);
 } 
```  
```s
 store_elem: (rdi, rsi, rdx) = (i, j, k)
 leaq (%rsi,%rsi,2),%rax // rax = 3 * j
 leaq (%rsi,%rax,4),%rax // rax = 4 * rax + j = 12 * j + j = 13 * j 
 movq %rdi,%rsi // rsi = i
 salq $6,%rsi // rsi = 64 * i 
 addq %rsi,%rdi // rdi = 65 * i 
 addq %rax,%rdi // rdi = 65 * i + 13 * j 
 addq %rdi,%rdx // rdx = 65 * i + 13 * j + k 
 movq A(,%rdx,8),%rax // rax = *( A + 8 * (65i + 13j + k))
 movq %rax,(%rcx) // *dest = rax
 movq $3640,%rax
 ret
```
zatem T = 13, czyli S = 65/13 = 5, stąd R = (3640/8)/(13*5) = 7 

## Zadanie 4 

zgaduję że a to coś w stylu : 
```c 
struct { 
    int idx; 
    int x[CNT]; 
} a_struct; 
``` 
ale póki co to jest tylko zgadnięcie z kodu z C. Teraz analiza assembly: 
```s
test: (rdi, rsi) -> (long i, b_struct *bp)
 movl 0x120(%rsi),%ecx // rcx = (bp + 288)* 
 addl (%rsi),%ecx // rcx = bp* + (bp + 288)*
 leaq (%rdi,%rdi,4),%rax // rax = 5i 
 leaq (%rsi,%rax,8),%rax // rax = 40i + bp
 movq 0x8(%rax),%rdx // rdx = (bp + 40i + 8)*
 movslq %ecx,%rcx // xd, jakies zerowanie 
 movq %rcx,0x10(%rax,%rdx,8) // (16 + bp + 40i + 8(bp + 40i + 8)* ) * = bp* + (bp + 288)*
 retq
```

## Zadanie 6 

```c
typedef struct A {
long u[2];
long *v;
} SA;
typedef struct B {
long p[2];
long q;
} SB
```

w rax ma zwracać Bm
```s 
eval:( rdi = SB* Bm , rsi = u[0], rdx = u[1], rcx = v*)  (SA s)
    movq %rdi, %rax // rax = wsk - 64
    movq 16(%rsp), %rcx // rcx = (wsk - 88)* = y /
    movq 24(%rsp), %rdx // rdx = (wsk - 80)* = wsk - 72 
    movq (%rdx), %rsi // rsi = (wsk - 72)* = z 
    movq %rcx, %rdx // rdx = y 
    imulq %rsi, %rdx // rdx = y * z
    movq %rdx, (%rdi) // Bm -> p[0] = y*z 
    movq 8(%rsp), %rdx // rdx = x 
    movq %rdx, %rdi // rdi = x
    subq %rsi, %rdi // rdi = x - z
    movq %rdi, 8(%rax) // Bm -> p[1] = x-z 
    subq %rcx, %rdx // rdx = x - y 
    movq %rdx, 16(%rax) // Bm -> q = x - y 
    ret
```

```s
 wrap: (rdi, rsi, rdx) = (long x, long y, long z)
subq $72, %rsp // rsp = wsk - 72
movq %rdx, (%rsp) // (wsk - 72)* = z 
movq %rsp, %rdx // rdx = wsk -72
leaq 8(%rsp), %rax // rax = wsk - 64
pushq %rdx // wrzuć na stos (wsk-80)* = wsk-72
pushq %rsi // wrzuć na stos (wsk - 88)* = y 
pushq %rdi // wrzuć na stos (wsk - 96) = x
movq %rax, %rdi // rdi = wsk - 64 
przy wywołaniu : rdi = wsk - 64, rsi = y, rdx = wsk - 72, 
call eval // 
movq 40(%rsp), %rax // rax = B -> p[1] = x -z 
addq 32(%rsp), %rax // rax = x - y + yz
imulq 48(%rsp), %rax // rax = (x-y+yz)*(x-z) = x*x -xy +xyz -xz +yz -yz^2
addq $96, %rsp
ret
```

```c 
typedef struct A {
long u[2];
long *v;
} SA;
typedef struct B {
long p[2];
long q;
} SB; 
SB eval(SA s){ 
    SB b; 
    b.p[0] = s.u[1]* (s.v*) 
    b.p[1] = s.u[0] - (s.v*); 
    b.q = s.u[0] - s.u[1]; 
}
long wrap (long x, long y, long z){ 
    SA a; a.u[0] = x; a.u[1] = y; a.v = &z; 
    SB b = eval(a); 
    return (b.p[0] + b.p[1]) * b.q;  
}
```

## Zadanie 7  
operacje : 
`vxorps` `a`,`b`,`c` - wykonuje `c` = `a` xor `b` dla rejestrów 128-bitowych (XMM)   
`vmovss` `src`,`dst` - przenosi dane z pamięci lub innego rejestu do jedneogo elementu(32-bitowego) w jednym z rejestrów xmm (xmm0 - xmm15), aby dostać się do odpowiedniej sekcji, użwyamy xmm1, xmm1[1], xmm1[2]...    
`vfmadd231ss` `x`,`y`,`z` - `x = y * z + x`  na skalarach, z dostosowaniem    
`vmulss` `a,b,
```s
puzzle7: (rdi = Struct P* , rsi = float x) 
    movq (%rdi), %rdx // rdx = P -> [0]
    leaq 8(%rdi), %rcx // rcx = P + 8 
    xorl %eax, %eax // rax = 0 
    vxorps %xmm1, %xmm1, %xmm1 // xmm1 = 0 
    vmovss .LC1(%rip), %xmm2 //  %xmm2 = .LC1 
    .L2: 
        cmpq %rdx, %rax 
        jge .L5 // jeśli rax >= rdx idź do .L5 
        vfmadd231ss (%rcx,%rax,4), %xmm2, %xmm1 // 
        incq %rax // rax += 1
        vmulss %xmm0, %xmm2, %xmm2 // xmm2 = xmm2 * xmm0 
        jmp .L2
    .L5:
        vmovaps %xmm1, %xmm0 // xmm0 = xmm1 
    ret
.LC1: .long 0x3f800000
```