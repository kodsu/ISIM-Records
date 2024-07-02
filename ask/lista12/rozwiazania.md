# Lista 12 ASK

## Zadanie 1 

### Teoria 
The case where two pointers may designate the same memory location is
known as **memory aliasing**. In performing only safe optimizations, the compiler
must assume that different pointers may be aliased.

### Praktyka
```c
void swap(long *xp, long *yp) {
 *xp = *xp + *yp; /* x+y */
 *yp = *xp - *yp; /* x+y-y = x */
 *xp = *xp - *yp; /* x+y-x = y */
 }
```
Nie może zostać dokonana optymalizacja, bo kompilator nie wie czy wskaźniki nie dotyczą tego samego miejsca w pamięci 

```c
 void swap2(long *xp, long *yp) {
    long x = *xp, y = *yp;
    x = x + y, y = x - y, x = x - y;
    *xp = x, *yp = y;
 }
```
kod bez opta:
```as
        movq    (%rsi), %rax
        addq    (%rdi), %rax
        movq    %rax, (%rdi)
        subq    (%rsi), %rax
        movq    %rax, (%rsi)
        subq    %rax, (%rdi)
        ret
```

kod z optem (restrict) `void swap(long *restrict xp, long *restrict yp)`: 
```as
swap:
        movq    (%rsi), %rax
        movq    (%rdi), %rdx
        movq    %rax, (%rdi)
        movq    %rdx, (%rsi)
        ret
```

## Zadanie 2 

### Teoria
**Czyste funkcje**, znane również jako "pure functions" w kontekście optymalizacji kodu, to funkcje, które mają dwie kluczowe właściwości:   
+ Brak efektów ubocznych (side effects): Czyste funkcje nie modyfikują żadnego stanu poza swoją lokalną przestrzenią. Oznacza to, że nie zmieniają globalnych zmiennych, nie zapisują do plików, nie modyfikują parametrów przez referencję itd.   
+ Deterministyczne wyniki: Dla tych samych argumentów wejściowych zawsze zwracają ten sam wynik. Innymi słowy, ich wyjście zależy wyłącznie od wartości argumentów wejściowych    
**Możliwość optymalizacji przez kompilator:**   
+ Eliminacja wywołań (Call Elimination): Jeśli kompilator wie, że funkcja jest czysta i wynik wywołania funkcji jest już dostępny, może pominąć dodatkowe wywołania tej funkcji, jeśli są one redundantne.  
+ Kachecie wyników (Memoization): Kompilator może przechowywać wyniki wywołań czystych funkcji, aby uniknąć ich ponownego obliczania przy tych samych argumentach.  
+ Inlining: Czyste funkcje są dobrymi kandydatami do inlining, ponieważ ich kod może być bezpiecznie wstawiony w miejsce ich wywołania bez obawy o efekty uboczne.    

deklarowanie funkcji **czystej**: 
```c
int __attribute__((pure)) foo(int x);
```

**Inlinowanie**: 
Inlinowanie funkcji to technika optymalizacji stosowana przez kompilatory, w której zamiast wywoływać funkcję w tradycyjny sposób (co wiąże się z pewnym narzutem czasowym związanym z operacjami na stosie), ciało funkcji jest bezpośrednio wstawiane w miejsce jej wywołania. Dzięki temu można zaoszczędzić czas wykonania związany z wywoływaniem funkcji oraz poprawić wydajność kodu.  
mamy słowo kluczowe, które sugeruje kompilatorowi inline'owanie `inline`  
```c
inline int add(int a, int b) {
    return a + b;
}
```
Ponadto jest flaga 
```
-finline=functions
```

### Praktyka 
kodzik funkcji
```c
#include<stddef.h> 
__attribute__((leaf)) /*__attribute__((pure))*/ 
size_t my_strlen(const char *s);

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
    if (s[i] == v)
        return &s[i];
    return 0;
}
```
kod assemblerowy bez modyfikacji: 
```s
my_index:
        pushq   %r12
        movl    %esi, %r12d
        pushq   %rbp
        xorl    %ebp, %ebp
        pushq   %rbx
        movq    %rdi, %rbx
.L2:
        movq    %rbx, %rdi
        call    my_strlen
        cmpq    %rax, %rbp
        jnb     .L8
        cmpb    %r12b, (%rbx,%rbp)
        jne     .L3
        leaq    (%rbx,%rbp), %rax
        jmp     .L1
.L3:
        incq    %rbp
        jmp     .L2
.L8:
        xorl    %eax, %eax
.L1:
        popq    %rbx
        popq    %rbp
        popq    %r12
        ret
```

kod assemblerowy po dodaniu atrybutu `pure`: 
```s
my_index:
        pushq   %rbp
        movl    %esi, %ebp
        pushq   %rbx
        movq    %rdi, %rbx
        pushq   %rcx
        call    my_strlen
        movq    %rax, %rdx
        movq    %rbx, %rax
        addq    %rbx, %rdx
.L2:
        cmpq    %rdx, %rax
        je      .L8
        leaq    1(%rax), %rcx
        cmpb    %bpl, (%rax)
        je      .L1
        movq    %rcx, %rax
        jmp     .L2
.L8:
        xorl    %eax, %eax
.L1:
        popq    %rdx
        popq    %rbx
        popq    %rbp
        ret
```

nowe `my_strlen`: 
```c 
__attribute__((leaf)) size_t static my_strlen(const char *s){ 
    int i = 0; 
    while(*(s+i) != '\0') 
        i++; 
    return i; 
}
```

(to jest sus ale po prostu wlepia się `strlen` zwykły)
```s
my_strlen:
        jmp     strlen
my_index:
        pushq   %rbp
        movl    %esi, %ebp
        pushq   %rbx
        movq    %rdi, %rbx
        pushq   %rcx
        call    my_strlen
        movq    %rax, %rdx
        movq    %rbx, %rax
        addq    %rbx, %rdx
.L3:
        cmpq    %rdx, %rax
        je      .L9
        leaq    1(%rax), %rcx
        cmpb    %bpl, (%rax)
        je      .L2
        movq    %rcx, %rax
        jmp     .L3
.L9:
        xorl    %eax, %eax
.L2:
        popq    %rdx
        popq    %rbx
        popq    %rbp
        ret
main:
        xorl    %eax, %eax
        ret
```
## Zadanie 3
### Teoria 
`niezmienniki pętli`(loop invariants), `zmienne indukcyjne`(induction variable) `osłabienie`(strength reduction)  
**Niezmiennik pętli** to wyrażenie, którego wartość nie zmienia się w trakcie wykonywania iteracji pętli. Niezmienniki pętli są używane przez kompilatory do optymalizacji kodu, ponieważ obliczenia związane z niezmiennikiem można przenieść poza pętlę, co zmniejsza liczbę operacji wykonywanych w każdej iteracji pętli.    
**Zmienne indukcyjne** to zmienne, które zmieniają swoje wartości w sposób regularny w każdej iteracji pętli. Zazwyczaj są one używane do zliczania iteracji lub indeksowania elementów tablicy.  
**Osłabienie** to technika optymalizacji, która polega na zastąpieniu kosztownych operacji arytmetycznych (np. mnożenia) mniej kosztownymi (np. dodawaniem). Kompilator identyfikuje takie operacje i zamienia je na bardziej efektywne.  


### Praktyka 
```c
void foobar(long a[], size_t n, long y, long z) {
     for (int i = 0; i < n; i++) {
        long x = y - z;
        long j = 7 * i;
            a[i] = j + x * x;
    }
}
```
kod assemblerowy
```s
foobar:
        subq    %rcx, %rdx # rdx:= y-z  
        xorl    %eax, %eax # rax = 0
        imulq   %rdx, %rdx # rdx:= (y-z)(y-z) <- 
.L2:
        cmpq    %rax, %rsi # jesli rax = n koniec
        je      .L5
        movq    %rdx, (%rdi,%rax,8) # a[i] = rdx
        incq    %rax # rax += 1
        addq    $7, %rdx # rdx += 7
        jmp     .L2
.L5:
        ret
```
**kod zrekonstuowany po optach w assemblerze**
```c 
void foobar(long a[], size_t n, long y, long z){ 
    z -= y; 
    z *= z; // <- kind of niezmiennik pętli
    for(int i = 0; i < n; i++){ 
        a[i] = z; 
        z += 7; // tutaj j pełniło rolę zmiennej indukowanej 
        // zastąpiliśmy też mnożenie dodawaniem, mamy więc osłabienie
    }
}
``` 

## Zadanie 4   

### Teoria   
`zmiany pętli`(loop interchage), `łączenia pętli` (loop fusion), `usuwanie zmiennych indukcyjnych` (induction variable elimination) 
`ponowne wyliczanie wartości` (rematerialization)    

**Zmiany pętli** to technika optymalizacji, która polega na zamianie kolejności zagnieżdżonych pętli. Jest to szczególnie przydatne, gdy dostęp do danych w pamięci może być bardziej efektywny przy zmianie kolejności pętli.  
**Łączenie pętli** to technika optymalizacji, która polega na połączeniu dwóch lub więcej pętli, które iterują po tych samych zakresach. Ma to na celu zmniejszenie liczby przejść przez pętlę i poprawę lokalności danych.  
**Usuwanie zmiennych** indukcyjnych to technika optymalizacji, która polega na eliminowaniu zmiennych indukcyjnych i zastępowaniu ich bezpośrednimi obliczeniami. Pomaga to zmniejszyć liczbę zmiennych i operacji w pętli.  
**Ponowne wyliczanie wartości** to technika optymalizacji, która polega na ponownym obliczeniu wartości zmiennej zamiast jej przechowywania i odczytywania z pamięci. Jest to szczególnie przydatne, gdy obliczenie jest tańsze niż dostęp do pamięci.   

### Praktyka 
```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k;
    for (long i = 0; i < n; i++)
        a[i * n] = a[i] = 0;
    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++)
            a[j * n + i] = i * j;
    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++)
            b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)];
 }
```
```s
compute2:
        movl    %edx, %ecx
        movl    $1, %eax
        pushq   %r12
        movq    %rsi, %r10
        sall    %cl, %eax
        pushq   %rbp
        movq    %rdi, %rcx
        xorl    %edx, %edx
        pushq   %rbx
        cltq
        leaq    0(,%rax,8), %rsi
.L2:
        cmpq    %rax, %rdx
        jge     .L14
        xorl    %r8d, %r8d
        movq    %r8, (%rdi,%rdx,8)
        incq    %rdx
        movq    %r8, (%rcx)
        addq    %rsi, %rcx
        jmp     .L2
.L14:
        leaq    (%rdi,%rsi), %r11
        movl    $1, %edx
.L4:
        cmpq    %rax, %rdx
        jge     .L15
        leaq    (%r11,%rdx,8), %r8
        movq    %rdx, %r9
        movl    $1, %ecx
.L5:
        incq    %rcx
        movq    %r9, (%r8)
        addq    %rdx, %r9
        addq    %rsi, %r8
        cmpq    %rcx, %rax
        jg      .L5
        incq    %rdx
        jmp     .L4
.L15:
        movq    %rdi, %r9
        movq    %rax, %rdx
        leaq    (%rax,%rax), %rbx
        movl    $1, %r8d
.L7:
        cmpq    %rax, %r8
        jge     .L16
        movq    %rdx, %rbp
        salq    $3, %rdx
        movl    $1, %ecx
        leaq    (%rdi,%rdx), %r12
        subq    %rax, %rbp
        addq    %r10, %rdx
.L8:
        movq    -8(%r9,%rcx,8), %r11
        addq    (%r12,%rcx,8), %r11
        movq    %r11, (%rdx,%rcx,8)
        incq    %rcx
        cmpq    %rcx, %rax
        jg      .L8
        incq    %r8
        leaq    (%rbx,%rbp), %rdx
        addq    %rsi, %r9
        jmp     .L7
.L16:
        popq    %rbx
        popq    %rbp
        popq    %r12
        ret
```

```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k;
    long i, j;

    // Zmienne pomocnicze
    long *end_a = a + n * n;
    long *ptr_a = a;
    long *ptr_b;
    long temp;

    // Pierwsza pętla: a[i * n] = a[i] = 0;
    for (i = 0; i < n; i++) {
        *ptr_a = 0;
        *(a + i) = 0;
        ptr_a += n;
    }

    // Druga pętla: a[j * n + i] = i * j;
    ptr_a = a + n;
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            *(ptr_a + j) = i * j; // tutaj moznaby lepiej, usunac mnozenie
        }
        ptr_a += n;
    }

    // Trzecia pętla: b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)];
    ptr_a = a + n;
    ptr_b = b + n;
    for (i = 1; i < n; i++) { // calkowita redukcja mnożeń 
        for (j = 1; j < n; j++) {
            temp = *(ptr_a + j - 1) + *(ptr_a - n + j - 1);
            *(ptr_b + j) = temp;
        }
        ptr_a += n;
        ptr_b += n;
    }
}
```
jakich optymalizacji zabrakło?   
+ Można pierwszą pętlę "włączyć w drugą, i tak nie odczytujemy wartości byłoby to `łączenie pętli`      
+ Tak naprawdę to można wszyskie trzy iteracje zrobić w jednej iteracji zagnieżdzonej, bo jak się okazuje, wcale nie potrzebujemy odczytywać niczego z `a`, gdyż `a[k] = (k/n) * (k%n)`.    
+ W ostatniej pętli można nie odwoływać sie do pamięci i korzystając z definicji `a` zastąpić:      

```c
b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)]
```
```c
b[i * n + j] = i * j + (i - 1) * (j - 1) 
``` 
A iloczyny można w podobny sposób wyliczać `zmiennymi indukowanymi` zamiast mnożyć to wszystko za każdym razem i będzie szybciej.  
Tak naprawdę koncepcyjnie jest to właśnie `ponowne wyliczenie wartości`. 
## Zadanie 5 

### Teoria 
`eliminacji wspólnych podwyrażeń` (common subexpression elimination) - optymalizacja, w której jednakowe wyrażenia zastępujemy, raz wyliczamy jego wartość i zapisujemy, a następnie wstawiamy w kilka miejsc. 

### Praktyka  
oryginalny kod: 
```c 
long neigh(long a[], long n, long i, long j) {
    long ul = a[(i-1)*n + (j-1)];
    long ur = a[(i-1)*n + (j+1)];
    long dl = a[(i+1)*n - (j-1)];
    long dr = a[(i+1)*n - (j+1)];
    return ul + ur + dl + dr;
}
```
po kompilacji: 
```s 
neigh:
        decq    %rdx #rdx = i-1
        leaq    -1(%rcx), %r8 # r8 = j-1
        incq    %rcx # rcx = j+1 
        imulq   %rsi, %rdx # rdx = (i-1)*n
        addq    %rsi, %rsi # rsi = 2*n 
        addq    %rdx, %rsi  # rsi = (i+1)*n
        leaq    (%rdx,%r8), %r9 # r9 = (i-1)*n + j-1
        addq    %rcx, %rdx # rdx = (i-1)*n + j+1
        movq    (%rdi,%rdx,8), %rax # rax = a[(i-1)*n + j+1]
        movq    %rsi, %rdx # rdx = (i+1)*n
        subq    %rcx, %rsi # rsi = (i+1)*n - (j+1)
        addq    (%rdi,%r9,8), %rax # rax += a[(i-1)*n + j-1]
        subq    %r8, %rdx # rdx = (i+1)*n - (j-1)
        addq    (%rdi,%rdx,8), %rax # rax += a[(i+1)*n - (j-1)]
        addq    (%rdi,%rsi,8), %rax # rax += a[(i+1)*n - (j+1)]
        ret
```
moja próba przepisania tego do C: 
```c
long neigh(long a[], long n, long i, long j){ 
    int x = (i-1)*n; n += n; int  y = x + n, e = j-1; j++; 
    int res = a[x + j]; 
    res += a[x + e]; 
    res += a[y - e];
    res += a[y - j];   
    return res; 
}
``` 
my try: 
```c
long neigh(long a[], long n, long i, long j) {
    long x = n*i, y = n - (j+1); 
    long *w = a + x; 
    long ans = *(w+y) + *(w +y + 2) + *(w-y) + *(w-y-2);  
    return ans; 
}
```
Ma 13 zamiast 16 w assemblerze. 

```s
neigh:
        imulq   %rsi, %rdx
        incq    %rcx
        subq    %rcx, %rsi
        leaq    0(,%rsi,8), %rcx
        leaq    (%rdi,%rdx,8), %rdx
        movq    (%rdx,%rsi,8), %rax
        addq    16(%rdx,%rsi,8), %rax
        movq    %rdx, %rsi
        subq    %rcx, %rsi
        addq    (%rsi), %rax
        addq    -16(%rsi), %rax
        ret
```

## Zadanie 7 

```c
void nonsense(long a[], long k,
    long *dp, long *jp) {
    long e = a[2];
    long g = a[3];
    long m = a[4];
    long h = k * 11;
    long f = g * h;
    long b = a[f];
    long c = e * 8;
     *dp = m + c;
     *jp = b + 4;
}
``` 

```s
nonsense:
        imulq   24(%rdi), %rsi
        movq    16(%rdi), %r8
        imulq   $11, %rsi, %rsi
        movq    (%rdi,%rsi,8), %rax
        movq    32(%rdi), %rsi
        addq    $4, %rax
        leaq    (%rsi,%r8,8), %rsi
        movq    %rsi, (%rdx)
        movq    %rax, (%rcx)
        ret
```


**Graf przepływu danych** to reprezentacja programu, która pokazuje przepływ danych między operacjami. Węzły w grafie reprezentują operacje (np. instrukcje), a krawędzie reprezentują zależności danych między tymi operacjami.

**Ścieżka krytyczna** w grafie przepływu danych to najdłuższa ścieżka od początku do końca, która określa minimalny czas wykonania programu. Każda operacja na tej ścieżce musi zostać zakończona, zanim następne operacje mogą się rozpocząć.

**Czas opóźnienia przetwarzania instrukcji** to liczba cykli zegara potrzebna do zakończenia wykonania danej instrukcji od momentu jej rozpoczęcia. Opóźnienia mogą się różnić w zależności od rodzaju instrukcji i architektury procesora.

