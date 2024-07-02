# Wykład z MP nr 7  -- zaczynamy klepać interpreter :)

opam install dune -- chcemy pracować w takim o narzędziu   

programy: 
**lekser** -- interpretuje napisy z naszego jezyka do tokenów 
**parser** -- "sklada tokeny w wyrazenia" 
**ast** -- abstract syntax tree (definiujemy jak składamy złożone typy) 

ast: 
``` 
type bop = Mult | Div | Add | Sub ;; 
type expr =  
	| Int of int 
	| Binop of bop * expr * expr 
;; 
Bindop(Add, Binop(Mult, Int 4 ,Int 2), 3);;   
```

najpierw piszemy parser zeby wiedziec jakie chcemy miec tokeny a pozniej lekser 

## Teraz to co chat gpt umie powiedzieć: 
W projekcie własnego interpretera wyrażeń arytmetycznych, podział zadań pomiędzy plikami może wyglądać następująco:

**ast.ml** - Ten plik zawiera definicje typów danych reprezentujących abstrakcyjne składniki syntaktyczne wyrażeń arytmetycznych, czyli tak zwane drzewo składniowe abstrakcyjne (AST). Na przykład, mogą być tam zdefiniowane typy dla różnych rodzajów operacji arytmetycznych, literałów liczbowych, zmiennych itp.

**lexer.mll** - Plik ten zawiera definicję leksera, czyli moduł odpowiedzialny za analizę tekstu wejściowego i podział go na leksemy. *Leksemy* to najmniejsze jednostki składniowe języka, takie jak liczby, operatory, słowa kluczowe, itp. W pliku lexer.mll definiuje się reguły, które opisują, jak rozpoznawać różne leksemy i przekształcać je na tokeny zgodne z wymaganiami parsera.

**parser.mly** - W tym pliku znajduje się definicja parsera, czyli modułu odpowiedzialnego za analizę składniową tekstu wejściowego na podstawie leksemów wygenerowanych przez lekser. Parser przetwarza sekwencje tokenów na struktury drzewa składniowego abstrakcyjnego (AST), które są bardziej wygodne do dalszej analizy i interpretacji.

**main.ml** - Plik główny, który może zawierać funkcję main lub inne funkcje odpowiedzialne za uruchomienie interpretera, obsługę wejścia i wyjścia, interakcję z użytkownikiem itp. W pliku main.ml można także wykorzystać moduły lexer, parser i ast do analizy i interpretacji wyrażeń arytmetycznych.

Podsumowując, każdy z tych plików pełni inną rolę w projekcie interpretera wyrażeń arytmetycznych:

    ast.ml - Definiuje struktury danych reprezentujące składnię abstrakcyjną.
    lexer.mll - Analizuje tekst wejściowy i generuje leksemy.
    parser.mly - Przetwarza leksemy na struktury drzewa składniowego abstrakcyjnego.
    main.ml - Uruchamia interpreter i obsługuje wejście/wyjście oraz inne funkcje aplikacji.

### Uruchamianie tego co napisaliśmy 

Aby skompilować projekt: 
```
cd calc
dune build
```
Aby uruchomić program: 
```
dune utop src
```
Następnie w utopie robisz: 
```
open Calc.Main;; 
interp "if 2 = 3 then 1 else 10 + 100";; 
```

## Gramatyki bezkontekstowe -- rewind/nauka  
Gramatyka bezkontekstowa $G = (V_N, V_T, P, S)$ składa się z  
+ $V_N$ -- zbioru symboli nieterminalnych. Np $V_N = \{E\}$, jedynym symbolem nieterminalnym jest $E$ reprezentującym wyrażenie arytmetyczne
+ $V_T$ -- zbiór symboli terminalnych(końcowych). Np $V_T=\{+,*,(,),num\}$
+ $P$ -- zbiór produkcji (reguł produkcji). Np. $P = \{E \rarr E+E, E \rarr E*E, E \rarr (E), E \rarr num\}$
+ $S$ -- zbiór symboli startowych.  
$S=E$ określa, że $E$ jest symbolem startowym gramytki, czyli reprezentuje wyrażenie arytmetyczne.  

**Uwaga:** Clue gramatyk bezkontekstowych jest takie że symbole produkjcji po lewej stronie zawierają jeden symbol nieterminalny, a po prawej dowolną kombinację symboli nieterminalnych i terminalnych. 




