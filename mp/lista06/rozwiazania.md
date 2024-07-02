# Rozwiązania zadań tekstowych do listy 6 z MP 

## Gramatyki bezkontekstowe -- rewind/nauka  
Gramatyka bezkontekstowa $G = (V_N, V_T, P, S)$ składa się z  
+ $V_N$ -- zbioru symboli nieterminalnych. Np $V_N = \{E\}$, jedynym symbolem nieterminalnym jest $E$ reprezentującym wyrażenie arytmetyczne
+ $V_T$ -- zbiór symboli terminalnych(końcowych). Np $V_T=\{+,*,(,),num\}$
+ $P$ -- zbiór produkcji (reguł produkcji). Np. $P = \{E → E+E, E → E*E, E → (E), E → num\}$
+ $S$ -- zbiór symboli startowych.  
$S=E$ określa, że $E$ jest symbolem startowym gramatyki, czyli reprezentuje wyrażenie arytmetyczne.  

**Uwaga:** Clue gramatyk bezkontekstowych jest takie że symbole produkcji po lewej stronie zawierają jeden symbol nieterminalny, a po prawej dowolną kombinację symboli nieterminalnych i terminalnych. 

## Zadanie 2 --- gramatyka języka palindromów 
Task: masz dany alfabet **$\Sigma = \{a,b\} $**, napisz gramatykę bezkontekstową języka palindromów nad **$\Sigma$**. 

+ symbole nieterminalne -- $V_N = \{E, K \}$
+ symbole terminalne -- $V_T = \{a, b,\epsilon \}$  
+ reguły produkcji -- $P = \{ E → EKE,~ E → K,~ K → a|b|\epsilon\}$ 
+ symbole startowe $S=E$, chociaż tego nie jestem do końca pewien. 
