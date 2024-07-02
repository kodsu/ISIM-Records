# Lista 14 ASK
## Zadanie 2
**Czemu dodanie TLB (ang. translation lookaside buffer) do jednostki zarządzania pamięcią (ang. memory management unit) przyspiesza translację adresów?**

Dodanie TLB przyspiesza translację adresów, ponieważ:

+ **Redukcja liczby odwołań do tablicy stron**: TLB działa jak cache dla tablicy stron, przechowując ostatnio używane mapowania adresów wirtualnych na fizyczne. Zamiast przeszukiwać wielopoziomowe tablice stron za każdym razem, gdy procesor potrzebuje translacji adresu, może szybko sprawdzić TLB, co jest znacznie szybsze.
+ **Szybszy dostęp**: TLB jest implementowana przy użyciu bardzo szybkiej pamięci SRAM, co pozwala na błyskawiczne wyszukiwanie i dostęp do mapowań adresów.
+ **Ominięcie złożoności tablicy stron**: Przeszukiwanie tablicy stron, zwłaszcza w systemach z wielopoziomową paginacją, może być skomplikowane i czasochłonne. TLB eliminuje tę złożoność dla większości odwołań pamięci.

**W jaki sposób różni się adresowanie TLB od adresowania pamięci podręcznej procesora?**

Adresowanie w TLB i pamięci podręcznej procesora różni się głównie w następujący sposób:

**Cel:**
+ TLB: Służy do mapowania adresów wirtualnych na fizyczne, wspierając jednostkę zarządzania pamięcią (MMU) w szybkiej translacji adresów.
+ Pamięć podręczna procesora (Cache): Służy do przyspieszenia dostępu do danych i instrukcji przechowywanych w głównej pamięci (RAM), buforując często używane dane
**Zawartość:**
+ TLB: Przechowuje pary mapowań (adres wirtualny -> adres fizyczny) oraz dodatkowe bity kontroli.
+ Cache: Przechowuje kopie danych i instrukcji z głównej pamięci, a także informacje takie jak tagi, dane i bity stanu.

**Mechanizm wyszukiwania:**   
+ TLB: Działa jak pamięć asocjacyjna lub z częściową asocjacją, gdzie szukanie odbywa się poprzez porównywanie tagów adresów wirtualnych.
+ Cache: Może być bezpośrednio skojarzona, w pełni asocjacyjna lub z częściową asocjacją, gdzie szukanie odbywa się na podstawie tagów adresów fizycznych.

**Zakres zastosowania:**
+ TLB: Skupia się tylko na adresach, które wymagają translacji.
+ Cache: Może przechowywać zarówno dane, jak i instrukcje, które już są w formie fizycznej.

**Kiedy ładowanie wpisu tablicy stron do TLB zakończy się wygenerowaniem wyjątku procesora?**

Ładowanie wpisu tablicy stron do TLB może zakończyć się wygenerowaniem wyjątku procesora w następujących sytuacjach:

+ **Brak wpisu w tablicy stron (Page Fault)**: Jeśli żądany adres wirtualny nie ma odpowiadającego mu wpisu w tablicy stron (na przykład strona nie została jeszcze załadowana do pamięci fizycznej), generowany jest wyjątek page fault.
+ **Niedozwolony dostęp**: Jeśli wpis tablicy stron wskazuje, że operacja (np. zapis) jest niedozwolona dla danego adresu (np. strona jest tylko do odczytu), generowany jest wyjątek ochrony (protection fault).
+ **Niepoprawny wpis**: Jeśli wpis tablicy stron jest nieprawidłowy (np. strona jest zaznaczona jako nieważna lub usunięta), generowany jest odpowiedni wyjątek.

**Czemu procesory używają osobnych TLB do tłumaczenia adresów instrukcji i danych?**

Procesory używają osobnych TLB do tłumaczenia adresów instrukcji (ITLB) i danych (DTLB) z kilku powodów:

+ **Równoległość operacji**: Umożliwia równoczesne tłumaczenie adresów dla pobieranych instrukcji i odczytywanych/zapisywanych danych, co zwiększa wydajność, ponieważ operacje te mogą być wykonywane jednocześnie.
+ **Optymalizacja wydajności**: Instrukcje i dane mają różne wzorce dostępu. Posiadanie osobnych TLB pozwala na optymalizację każdej z nich pod kątem specyficznych wzorców dostępu.
+ **Redukcja konfliktów:** Separacja ITLB i DTLB zmniejsza ryzyko konfliktów w dostępie do TLB, co mogłoby prowadzić do dodatkowych opóźnień w przetwarzaniu.
+ **Lepsze zarządzanie**: Rozdzielone TLB pozwalają na bardziej precyzyjne zarządzanie translacją adresów i zasobami pamięci w zależności od rodzaju operacji (instrukcja vs dane), co może poprawić ogólną efektywność systemu.
Wydruk z `cpuid -1` czyli wydruku dla pierwszego procesora czy coś: 
```
 L1 TLB/cache information: 2M/4M pages & L1 TLB (0x80000005/eax):
      instruction # entries     = 0x40 (64)
      instruction associativity = 0xff (255)
      data # entries            = 0x40 (64)
      data associativity        = 0xff (255)
   L1 TLB/cache information: 4K pages & L1 TLB (0x80000005/ebx):
      instruction # entries     = 0x40 (64)
      instruction associativity = 0xff (255)
      data # entries            = 0x40 (64)
      data associativity        = 0xff (255)
``` 
1. Liczba wpisów w L1 TLB
+ Instruction TLB: 64 wpisy dla instrukcji. 
+ Data TLB: 64 wpisy dla danych.

2. Asocjacyjność L1 TLB

+ Instruction TLB: Asocjacyjność wynosi 255 (0xff).
+ Data TLB: Asocjacyjność wynosi 255 (0xff).

3. Interpretacja asocjacyjności

Wartość 0xff (255) dla asocjacyjności oznacza, że TLB jest w pełni asocjacyjna. W pełni asocjacyjna pamięć oznacza, że każdy wpis może być umieszczony w dowolnym miejscu w TLB. Jest to najefektywniejsza forma asocjacyjności, ponieważ minimalizuje konflikty i maksymalizuje wykorzystanie dostępnych zasobów.

4. Rodzaje stron

Informacje są podzielone na dwa typy stron:
+ 2M/4M pages: TLB obsługuje strony o rozmiarze 2MB i 4MB.
+ 4K pages: TLB obsługuje również standardowe strony o rozmiarze 4KB.