


Tw.  Dla dowolnych list xs i ys istnieje lista zs taka, że append xs ys ≡ zs
Indukujemy się względem xs.

1. Pokażę, że dla każdego ys istnieje zs takie, że: append [] ys ≡ zs
append [] ys
==(def. append)
ys
==(przypisanie)
zs

2.
Weźmy dowolne xs. Załóżmy, że dla każdego ys istnieje zs, że
   zachodzi append xs ys ≡ zs,
   pokażę, że dla każdego ys,x istnieje zs, takie, że
   zachodzi append x::xs ys ≡ zs
  
append x::xs ys
==(def. append)
x:: append xs ys
==(zał. ind.)
x :: zs'
==(podstawienie)
zs