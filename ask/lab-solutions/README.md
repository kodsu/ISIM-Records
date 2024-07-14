# Lab Solutions

This directory contains solutions to various practical tasks for the course **Computer System Architectures**. Each file implements a specific function in x86-64 assembly, aiming for minimal instruction count and low CPI.

## Files and Descriptions

### bitrev.s
- **Function**: `uint64_t bitrev(uint64_t)`
- **Description**: Reverses the bits of the given machine word. For a word composed of bits $b_{n-1}...b_0$, where $b_i \in \{ 0,1 \}$, the function returns a word where the bits are mirrored such that $r_i = b_{n-1-i}$ .
- **Complexity**: $O(log \ n)$, where $n$ is the bit length of the machine word.
- **Constraints**: No longer than $32$ instructions.

### addsb.s
- **Function**: `uint64_t addsb(uint64_t a, uint64_t b)`
- **Description**: Performs saturated addition of two $8$-element vectors of `int8_t` values stored in `uint64_t` machine words. Saturation arithmetic ensures values are clamped at the range limits (e.g., $80 + 60 = 127$ and $-40 + -100 = -128$).
- **Constraints**: No longer than $36$ instructions.

### clz.s
- **Function**: `int clz(uint64_t)`
- **Description**: Counts the number of leading zeros in the given machine word.
- **Complexity**: $O(log \ n)$, where $n$ is the bit length of the machine word.
- **Constraints**: No longer than $50$ instructions and must not use jump instructions.

### mod17.s
- **Function**: `int mod17(uint64_t)`
- **Description**: Computes the remainder of the given number when divided by $17$ without using multiplication or division instructions.
- **Constraints**: No longer than $35$ instructions and must not use control flow instructions (except for `ret`). Usage of `div` or `idiv` is prohibited.

### wbs.s
- **Function**: `uint64_t wbs(uint64_t)`
- **Description**: Computes the weighted sum of the bits in the given machine word. The weight of bit $b_i$ is $i$, so the result is   $\sum\limits_{i=0}^{n-1} (b_i * i)$.
- **Complexity**: $O(log \ n)$, where $n$ is the bit length of the machine word.
- **Constraints**: No longer than $50$ instructions. Usage of `popcount` is prohibited.

---

# Rozwiązania Pracowniane

Ten folder zawiera rozwiązania różnych zadań praktycznych dla kursu **Architektury Systemów Komputerowych**. Każdy plik implementuje specyficzną funkcję w asemblerze x86-64, dążąc do minimalnej liczby instrukcji oraz niskiego CPI.

## Pliki i Opisy

### bitrev.s
- **Funkcja**: `uint64_t bitrev(uint64_t)`
- **Opis**: Odwraca bity danego słowa maszynowego. Dla słowa składającego się z bitów  $b_{n-1}...b_0$, where $b_i \in \{ 0,1 \}$, zwraca słowo z bitami odbitymi lustrzanie, tak że $r_i = b_{n-1-i}$. 
- **Złożoność**: $O(log  \ n)$, gdzie n to długość słowa maszynowego w bitach.
- **Ograniczenia**: Nie dłuższe niż $32$ instrukcje.

### addsb.s
- **Funkcja**: `uint64_t addsb(uint64_t a, uint64_t b)`
- **Opis**: Wykonuje dodawanie z nasyceniem dwóch ośmioelementowych wektorów wartości typu `int8_t` przechowywanych w słowach maszynowych typu `uint64_t`. W arytmetyce z nasyceniem wartości są ograniczone do zakresu (np. $80 + 60 = 127$, a $-40 + -100 = -128$).
- **Ograniczenia**: Nie dłuższe niż $36$ instrukcji.

### clz.s
- **Funkcja**: `int clz(uint64_t)`
- **Opis**: Zlicza liczbę wiodących zer w danym słowie maszynowym.
- **Złożoność**: $O(log \ n)$, gdzie $n$ to długość słowa maszynowego w bitach.
- **Ograniczenia**: Nie dłuższe niż $50$ instrukcji i nie używa instrukcji skoków.

### mod17.s
- **Funkcja**: `int mod17(uint64_t)`
- **Opis**: Oblicza resztę z dzielenia danej liczby przez $17$ bez użycia instrukcji mnożenia lub dzielenia.
- **Ograniczenia**: Nie dłuższe niż $35$ instrukcji oraz nie używa instrukcji sterujących (poza `ret`). Użycie instrukcji `div` lub `idiv` jest zabronione.

### wbs.s
- **Funkcja**: `uint64_t wbs(uint64_t)`
- **Opis**: Oblicza ważoną sumę bitów danego słowa maszynowego. Waga bitu $b_i$ wynosi $i$, więc wynikiem jest $\sum\limits_{i=0}^{n-1} (b_i * i)$.
- **Złożoność**: $O(log \ n)$, gdzie $n$ to długość słowa maszynowego w bitach.
- **Ograniczenia**: Nie dłuższe niż $50$ instrukcji. Użycie `popcount` jest zabronione.
