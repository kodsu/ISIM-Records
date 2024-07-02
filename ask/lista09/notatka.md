# Podatność kodu na ataki   
Uwaga do proprzedniego tematu:   
**Rekord relokacji** -- gdy mamy symbole w tekście, których assembler nie zna, wstawia tam informację o tym, że nie znany jest symbol. 

Main część - o układzie pamięci i o tym jak można atakować aplikacje. 
Każdy program dysponuje swoją wlasna przestrzenią adresową. 
```sh
pmap $$ 
```
Pokazuje to naszą obecną przestrzeń adresową.  

`Shared space` 
`Stack (8MB)`  
`free space`  (sterta)
`Heap`   (sterta dla małych bloków)
`bss`  
`Data`  
`Text` 
`blank space` (chodzi o to żeby nie można było dereferencjonować Null pointera) 

```c 
char big_array[1<<24]; // zostanie prypisane w bss 
int global = 10; // zostanie wpisany w Data  
int useless() { return 0; } // zostanie wpisane w text 

int main(){ 
    void *phuge, *psma112; // zostanie wpsiany do rejestrów albo na stos
    int loccal = 0; // na stossie jest     
    //stos nie jest automatycznie czyszczony i mogą tam być śmieci
    phuge = malloc(1 << 256 ); // do wolnych danych (free space) zostanie to przypisane 
  
}
```

komenda do wglądu bloków pamięci: 
```sh
readelf -h -l ropex
```
Jak można sobie strzelić w stopę?   
Stos jest skończonym zasobem i ma `8 MB`. Można go sobie skończyć, jeśli np inicujejmy tablice w schodząc w rekursji.  
`volatile` - zmusi kompilator aby wrzucić strukturę na stosie 

## Atak! 
Za pomocą przepełnienia stosu można zaatakować program. Sprawia to, że 
można zaatakować nasz program i zmusić go do przejścia do innych programów czy uruchomienia złośliwego oprogramowania. Dzieje się to często poprzez nadpisanie adresu powrotu funkcji do innego adresu, wywolującego złośliwy program.  
Jest to jedna z najczęstszych technik atakowania oprogramowania, która jest możliwa dzięki ignoracji programistów, którzy nie myślą za dużo o lokowanej na stosie pamięci, myśląc: **kto miałby to niby wykorzystać**.    
Z jednej strony wiedza o tych atakach jest bardziej powszechna i istnieją różna narzędzia zabezpieczające, ale nie jest to uniwersalne i dalej da się tak hackować, choć jest to istotnie trudniejsze.

## Get this done 
Tworzymy sobie jakąs prostą funkcję do której będziemy przekierowywać atakowwać naszą funkcję - `smash`. Za pomocą `objdump` potrzebujemy poznać adres naszej funkcji gadżetowej. W adresie nie może być `0x0a`, gdyż zostnie to odczytane jako `\0` i funkcja się zakończy.  
```sh 
objdump -d echo | less 
```
(kod do poznania adresu funkcji chyba) 
 
**Code injection attack**   
Do bufora wczytujemy instrukcje programu, np odpalały shella i wykonywały tam jakieś instrukcje. Następnie ten bufor musimy wrzucić na stos. Następnie tak ustalamy adres powrotny, aby jakaś funkcja do niego skoczyła.  
**Problem:** Czy pamięć na stosie jest wykonywalna?   
W nowoczesnych architekturach nie jest, więc ta metoda jest dosyć archaiczna.  

## Jak tego unikać? 
Używajmy funkcji, które przjmują informację o rozmiarze bufora, który chcemy wczytywać.  
Zamiast `gets` użyj `fgets`. Zamiast `strcpy` używaj `strncpy`. Ponasto nie używaj `scanf("%s", &wsk)`. Zamiast tego można użyć `fgets`. Pamiętaj, że są lepsze funkcje, które nie wywołują bólu głowy.  
Uzywajmy zabezpieczeń od systemu operacyjnego. Możemy robić taką sztuczkę, która za kazdym razem przypisze stos pod innym adresem, bedziemy wtedy mniej podatni na taki atak, hacker potrzebuje znać adres stosu.  Będzie mógł to zbrutować, ale to zajmuje już więcej zasobów.  
Czy oczekujemy, że procesor powinien móc wykonywać zawartość stosu? 
W większości nowych systemów stos jest niewykonywalny, co utrudnia życie hackerom.  
**Kanarki**  
Kiedyś do kopalni zabierano kanarek, aby odczytywać wycieki metanu.  
Co to ma do codingu? 
Ustawiamy 8 bajtów **kanarka**, które wywalają nam program, gdy zostaną zmodyfikowane. Zabezpiecza to nas trochę przed majstrowaniem przy stosie.   
`-fstack-protector`

A usuwa to `-fno-fstack-protector` 
Inne zabezpieczenia (utrudnienia dla hackerów):   
+ Randomizajca stosu 
+ Niewykonwyaly stos  
Kocept tricka:  
Zbieramy `użyteczne małe kawałeczki kodu` aka `gadżety` z różnych miejsc programu, które zlepimy tak, żeby to dobrze działało.    
Jak przed tym się zabezpieczamy? 
Dokonujemy randomizacji przestrzeni adresowych dla funkcji. 
Ale nie jest to ostateczne zabezpiecznie... 
