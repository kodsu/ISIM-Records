Pokaż, że funkcja append zawsze oblicza się do wartości, tzn. pokaż, że dla do-
wolnych list xs i ys istnieje lista zs taka, że append xs ys ≡ zs  

let rec append xs ys =
  match xs with
  | [] -> ys
  | x :: xs' -> x :: append xs' ys

Pokażę, T(n) -- dla dowolnej listy xs dlugosci n oraz dla dowolnej listy ys istnieje 
lista zs taka, że  
append xs ys = zs 

1. T(0) 
append [] ys 
== (def. append)
 ys, wiec takie zs istnieje 

2. T(n) => T(n+1) 
tzn jeśli tw zachodzi dla xs to zachodzi tez dla x::xs 

append x::xs ys 
== (def. append) 
x :: (append xs ys) 
== (zał. ind) 
x :: zs 
== (ocaml) 
zs'
Stąd teza. 