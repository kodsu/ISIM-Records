# Lista 13 z ASKa -- Jakub Szydło

# Zadanie 1

### Profilowanie programów

Profilowanie programów ma na celu zebranie danych dotyczących wydajności programu w trakcie jego działania. Celem jest zidentyfikowanie, które części programu wymagają najwięcej czasu wykonania i powinny być zoptymalizowane w celu poprawy ogólnej wydajności. Profilowanie jest szczególnie użyteczne przy pracy z dużymi programami, gdzie ręczne określenie miejsc do optymalizacji może być trudne.

### Profil płaski (flat profile)

Profil płaski dostarcza listę wszystkich funkcji wywoływanych w trakcie wykonania programu wraz z liczbą wywołań i czasem wykonania, za który każda funkcja jest odpowiedzialna. Funkcje są wymienione w kolejności malejącej według czasu wykonania. Profil płaski pozwala na szybkie zorientowanie się, które funkcje są najbardziej czasochłonne i mogą wymagać optymalizacji. Zazwyczaj pokazuje, że żadna pojedyncza funkcja nie jest przyczyną większości czasu wykonania programu. Czasy poszczególnych funkcji sumują się do całkowitego czasu wykonania programu.

### Profil grafu wywołań (call graph profile)

Profil grafu wywołań zawiera informacje o relacjach między funkcjami, pokazując, które funkcje wywołują inne oraz ile czasu na nie przypada (zarówno bezpośrednio, jak i przez wywołania potomne). W przeciwieństwie do profilu płaskiego, profil grafu wywołań uwzględnia dziedziczony czas wykonania, co pozwala zrozumieć wpływ wywołań funkcji wyższego poziomu na czas wykonania programu. Profil ten pokazuje, jak duży procent czasu funkcji nadrzędnych przypada na wywołania funkcji podrzędnych, co pomaga zidentyfikować wąskie gardła w hierarchii wywołań.

### Specjalna opcja kompilatora «-pg»

Profilowanie programu wymaga zbudowania go ze specjalną opcją kompilatora «-pg», ponieważ ta opcja dodaje do kodu programu dodatkowe instrukcje (instrumentację), które zbierają dane o wydajności. Bez tej opcji kod programu nie zawierałby niezbędnych mechanizmów do śledzenia czasu wykonania poszczególnych funkcji i liczby wywołań, co jest kluczowe dla przeprowadzenia profilowania.

### Zliczanie interwałowe (interval counting)

Zliczanie interwałowe polega na tym, że system operacyjny co pewien regularny interwał czasowy (zwykle od 1.0 do 10.0 milisekund) przerywa działanie programu i sprawdza, która funkcja była wykonywana w momencie przerwania. Licznik czasu dla tej funkcji jest zwiększany o wartość tego interwału. Ta metoda może być niedokładna w krótkich okresach, ale statystycznie dobrze oddaje względny czas wykonania poszczególnych funkcji w dłuższym czasie. Dla programów, które działają krócej niż około 1 sekundę, uzyskane wartości są jedynie przybliżone.

## Zadanie 2

musimy wybrać opcje z 
```cpp 
oraz rozmiar n-gramu [?] 
{lower1, lower2};
{h_mod, h_add, h_xor}; 
{find_ele_rec, find_ele_iter_f, find_ele_iter_r}; 
oraz quick (0/1)
```
first run: 
```
Total time = 120.645636 seconds
```
zmieniam quick na 1  używamy quicksorta w $O(n log n)$ zamiast sortowania w $O(n^{2})$ 
second run: 
```
Total time = 8.418317 seconds
``` 
zmieniam findele_rec na find_ele_iter_f -- zamiana rekursywnego przeszukiwania listy na iteracyjne na wskaźnikach, gdy nie znajdziemy dokładamy element na początek
third run: 
```
Total time = 12.624922 seconds
```

zmieniam find_ele_iter_f na find_ele_iter_r -- zamiana z dodawania na poczatek listy na dodawania na koniec (późniejsze elementy są rzadsze ~ heura)
4th run: 
```
Total time = 7.566387 seconds
```
jest lepiej, pora poeksperymentować z hashowaniem

odpalam teraz `h_add` zamiast `h_mod`
```
Total time = 11.313613 seconds
``` 
jest gorzej  
może `h_xor`  

```
Total time = 7.493858 seconds
``` 
a bit lepiej, teraz podmieniam lower1 na lower2 
```
Total time = 7.789442 seconds
``` 
jest gorzej 

Skokowe ulepszenie - zmiana size na `500000` (wyznaczone *ternarnie*)
```
Total time = 0.384645 seconds
```
## Zadanie 3 
`strtok` -- 
```cpp
#include <cstring>
char * strtok( char * str, const char * korektor );
```
Funkcja zastępuje pierwszy znaleziony znak w str znakiem terminalnym. Pulę szukanych znaków określa argument korektor. 
`qsort` -- robi quicksorta

`malloc` -- rezerwuje nam dynamicznie pamięć   

### potencjalne optymalizacje:  

+ Funkcja lower2:  
    Zamiast używać warunku if (s[i] >= 'A' && s[i] <= 'Z'), można zastosować tablicę konwersji, co może zredukować liczbę instrukcji warunkowych.  
+ Funkcja Strlen:  
    Jeśli to możliwe, należy zawsze używać standardowej biblioteki strlen, która może być zoptymalizowana na poziomie asemblera przez kompilator.  
+ Funkcja new_ele:    
    Unikaj podwójnego wywoływania Strlen. Można przekazywać długość słowa jako argument do new_ele.  
+ Funkcja h_xor:  
    Zoptymalizować pętlę obliczeniową poprzez użycie instrukcji SIMD, jeśli są dostępne.  
+ Funkcja get_word:  
    Można zminimalizować wywołania strtok przez bardziej efektywne przetwarzanie bufora wejściowego.  
Dla `qsort` należy użyć możliwie najprostszej f.sortującej: 
```cpp 
int compare_ele(const void *vele1, const void *vele2) {
  h_ptr ele1 = *(h_ptr *)vele1;
  h_ptr ele2 = *(h_ptr *)vele2;
  return ele2->freq - ele1->freq;
}
```
`malloc` - jeśli to możliwe, to mallocować rzadziej i więcej niż częścniej i mniej 
`str_cpy` - jeśli się da, to używać wersji, która przyjmuje za argument też liczbę znaków 

## Zadanie 4 
Pojęcie regionu fizycznej przestrzeni adresowej odnosi się do zakresu adresów fizycznych, które są dostępne i zarządzane przez system komputerowy. Fizyczna przestrzeń adresowa to rzeczywista przestrzeń adresów pamięci (RAM) w komputerze, w przeciwieństwie do wirtualnej przestrzeni adresowej, która jest używana przez procesy w systemie operacyjnym.

Region fizycznej przestrzeni adresowej to określony zakres adresów w tej fizycznej przestrzeni, który jest zazwyczaj przypisany do określonych urządzeń lub obszarów pamięci. Przykładami takich regionów mogą być:  

**RAM** – Główna pamięć operacyjna komputera.  
**ROM** – Pamięć tylko do odczytu, która może zawierać np. BIOS.  
**Pamięci urządzeń peryferyjnych** – Obszary przypisane do różnych urządzeń peryferyjnych, takich jak karty sieciowe, karty graficzne, kontrolery dysków itp.  


## Zadanie 6 
Przypadki, w których instrukcja mov może zgłosić wyjątek błędu dostępu do pamięci   

Procesor może zgłosić wyjątek błędu dostępu do pamięci (ang. memory access violation) w przypadku instrukcji mov w następujących sytuacjach: 

+ Dostęp do nieistniejącej strony: Próba odczytu lub zapisu do adresu, który nie ma odpowiadającej mu strony w tabeli stron. Przykład: mov eax, [0xDEADBEEF] (jeśli adres 0xDEADBEEF nie jest zmapowany).
+ Dostęp do strony bez odpowiednich praw: Próba zapisu do strony oznaczonej jako tylko do odczytu lub próba odczytu/zapisu do strony bez odpowiednich praw użytkownika.
    Przykład: mov [0x400000], eax (jeśli strona 0x400000 jest tylko do odczytu).
+ Dostęp do nieosiągalnego obszaru pamięci: Próba odczytu lub zapisu do obszaru pamięci, który jest oznaczony jako niewidoczny lub chroniony Przykład: mov eax, [0xFFFFFFFF] (jeśli obszar ten jest poza zakresem dostępnej pamięci).
+ Dostęp do pamięci po zwolnieniu strony: Próba odczytu lub zapisu do strony, która została zwolniona (np. przez free lub munmap).
Przykład: mov eax, [0x12345678] (jeśli adres ten został wcześniej zwolniony).  


Przypadki, które zawsze spowodują zakończenie programu z błędem, to:  

+ Dostęp do nieistniejącej strony, jeśli nie można jej załadować z dysku (np. w przypadku braku miejsca na swap lub błędu I/O).   
+ Dostęp do strony bez odpowiednich praw, jeśli nie można zmienić praw dostępu do strony.   
+ Dostęp do nieosiągalnego obszaru pamięci.   
+ Dostęp do pamięci po zwolnieniu strony.   

W tych przypadkach system operacyjny zazwyczaj zgłosi wyjątek typu "segmentation fault" lub inny rodzaj błędu ochrony pamięci, co prowadzi do natychmiastowego zakończenia programu.
Procedura obsługi błędu strony (ang. page fault)

Procedura obsługi błędu strony jest odpowiedzialna za:

+ Identyfikację przyczyny błędu strony: Sprawdzenie, dlaczego strona pamięci nie jest dostępna (brak strony, brak praw dostępu, itp.).
+ Obsługę żądania strony: Jeśli strona nie jest obecna w pamięci (np. została wymieniona na dysk), procedura może załadować stronę z dysku do pamięci.
+ Aktualizację tabeli stron: Zaktualizowanie wpisu w tabeli stron, aby odzwierciedlać, że strona jest teraz dostępna w pamięci i ma odpowiednie prawa dostępu.

Co się dzieje przed i po wykonaniu procedury obsługi błędu strony
Przed wykonaniem procedury obsługi błędu strony:

+ Wywołanie wyjątku: Procesor wykrywa błąd strony i wywołuje odpowiedni wyjątek.
+ Zapisywanie kontekstu: Stan procesora, w tym adres wywołujący błąd i kod błędu, jest zapisywany, aby procedura obsługi mogła zidentyfikować przyczynę i miejsce błędu.

Po wykonaniu procedury obsługi błędu strony:

+ Aktualizacja tabeli stron: Procedura obsługi błędu strony aktualizuje tabelę stron, aby odzwierciedlać nowe mapowanie.
+ Kontynuacja wykonywania programu: Jeśli błąd strony został poprawnie obsłużony (np. strona została załadowana do pamięci), program może kontynuować wykonywanie od miejsca, w którym wystąpił błąd.
+ Zgłoszenie błędu: Jeśli błąd strony nie może być obsłużony (np. brak miejsca na załadowanie strony), procedura może zgłosić błąd do systemu operacyjnego, który zazwyczaj kończy program i zgłasza "segmentation fault" lub inny odpowiedni błąd. 

## Zadanie 7 
Rejestr sterujący CR3 w procesorach x86-64
Co przechowuje rejestr CR3?

Rejestr sterujący CR3 w procesorach x86-64 przechowuje fizyczny adres bazowy tablicy stron (Page Table Base Address). Jest to struktura danych używana przez mechanizm pamięci wirtualnej do przeprowadzania translacji adresów logicznych (wirtualnych) na adresy fizyczne. Dokładnie, CR3 zawiera:  

+ Fizyczny adres tablicy poziomu 4 (PML4): Adres ten wskazuje na początek hierarchii tablic stron używanych do translacji adresów w trybie stronicowania.
+ Bity stanu zarządzania cache'owaniem: Bity te kontrolują, jak pamięć wskazana przez tablicę stron powinna być cachowana.

**Dlaczego jest dostępny wyłącznie w trybie uprzywilejowanym (supervisor mode)?**

Rejestr CR3 jest dostępny wyłącznie w trybie uprzywilejowanym (supervisor mode) z kilku kluczowych powodów:

+ Bezpieczeństwo: Tablica stron kontroluje mapowanie całej przestrzeni adresowej procesu. Jeśli użytkownik mógłby zmodyfikować CR3, mógłby potencjalnie uzyskać dostęp do dowolnej pamięci w systemie, w tym do pamięci innych procesów i pamięci jądra. To mogłoby prowadzić do poważnych naruszeń bezpieczeństwa.
+ Stabilność systemu: Nieautoryzowane modyfikacje CR3 mogłyby prowadzić do błędów w mapowaniu pamięci, co skutkowałoby awariami systemu, błędami stron i niestabilnością.
+ Izolacja procesów: Utrzymywanie CR3 dostępnego tylko dla trybu uprzywilejowanego zapewnia, że każdy proces ma izolowaną przestrzeń adresową. Zmiany w tablicy stron mogą być dokonywane tylko przez system operacyjny, co zapewnia kontrolę nad tym, które adresy wirtualne są mapowane do których adresów fizycznych.

**Czy moglibyśmy zagwarantować izolację, jeśli pamięć przechowująca tablicę stron była dostępna w trybie użytkownika?**

Nie, nie moglibyśmy zagwarantować izolacji, jeśli pamięć przechowująca tablicę stron była dostępna w trybie użytkownika. Oto dlaczego:

+ Modyfikacja mapowań: Gdyby użytkownik mógł zmieniać tablicę stron, mógłby manipulować mapowaniami adresów, uzyskując dostęp do pamięci innych procesów lub jądra. + Mogłoby to prowadzić do eskalacji uprawnień, gdzie użytkownik mógłby przejąć kontrolę nad całym systemem.
+ Ominięcie mechanizmów bezpieczeństwa: System operacyjny polega na tym, że tablice stron są zaufane i nie mogą być modyfikowane przez użytkownika. Dostęp użytkownika do tych struktur umożliwiłby ominięcie wielu mechanizmów ochrony pamięci.
+ Nieprzewidywalne zachowanie systemu: Użytkownicy mogliby wprowadzać niepoprawne mapowania, co prowadziłoby do częstych błędów stron, awarii aplikacji i ogólnej niestabilności systemu.

Z tych powodów pamięć przechowująca tablicę stron musi być dostępna wyłącznie w trybie uprzywilejowanym. System operacyjny może zarządzać tymi strukturami, zapewniając prawidłową izolację procesów, integralność pamięci oraz bezpieczeństwo całego systemu.