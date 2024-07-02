let is_sorted xs =
  let rec pom xs last =
    match xs with
    | [] -> true
    | x::xs' -> if x >= last then pom xs' x else false
  in pom xs min_int;;

let rec insert el xs =
  match xs with 
  | [] -> [el]
  | x::xs' -> if el<=x then (el :: xs) else (x :: (insert el xs'));;

is_sorted [1;2;6;72;73];;

insert (-1) [1;2;6;72;73];;

Tw. Dla dowolnej tablicy xs i dowolnego int'a x zachodzi
is_sorted xs ≡ true => is_sorted (insert x xs) ≡ true

1. Udowdnijmy is_sorted (insert x []) ≡ true

is_sorted (insert x [])
==(def. insert)
is_sorted [x]
==(def. is_sorted)
pom [x] min_int
==(def. pom, wszystko jest większe od min_int)
pom [] x
==(def. pom)
true


Lemat: y>=x => (pom (y::xs) x ≡ is_sorted y::xs)

2.
Teraz załóżmy, że dla dowolnej tablicy xs i dowolnych liczb x,y zachodzi:
is_sorted xs ≡ true => is_sorted (insert x xs) ≡ true
i udowdnijmy, że zachodzi: is_sorted y::xs ≡ true => is_sorted (insert x (y :: xs)) ≡ true


1. Jeżeli xs puste
is_sorted (insert x (y :: []))
==
is_sorted (insert x [y])
a)Jeżeli x<=y
== 
is_sorted(x::[y])
==
is_sorted([x;y])
==
pom [x;y] min_int
==
pom [y] x
==
pom [] y
==
true

b)Jeżeli x>y
== 
is_sorted(x::[y])
==
is_sorted([y;x])
==
pom [y;x] min_int
==
pom [x] y
==
pom [] x
==
true

2. Jeżeli xs niepuste i y>xs[0]
is_sorted y::xs
==
pom y::xs min_int
==
pom xs y
==(istnieje z taki, że z == xs[0])
pom (z::xs') y
==(bo y>z)
false
Zatem implikacja (is_sorted y::xs ≡ true => is_sorted (insert x (y :: xs)) ≡ true) jest prawdziwa



3. Jeżeli xs niepuste i y<=xs[0]

a) Jeżeli x<=y
is_sorted (insert x (y :: xs))
==
is_sorted (x :: y :: xs)
==(def. is_sorted)
pom (x :: y :: xs) min_int
==(def. pom)
pom (y::xs) x
==(Lemat)
is_sorted y::xs

b)Jeżeli x>y
is_sorted (insert x (y :: xs))
==(def. is_sorted)
pom (insert x (y :: xs)) min_int
==(def. insert)
pom (y:: insert x xs) min_int
==(def. pom)
pom (insert x xs) y
==(Lemat, dziala bo y<x i y<=xs[0])
is_sorted (insert x xs)

1) Jeżeli is_sorted xs ≡ true
==(zał. ind)
true

2) Jeżeli is_sorted xs ≡ false
is_sorted y::xs
==
pom y::xs min_int
==
pom xs y
==(Lemat)
is_sorted xs
==
false

Zatem implikacja (is_sorted y::xs ≡ true => is_sorted (insert x (y :: xs)) ≡ true) jest spełniona.


Teraz udowadnijmy lemat z którego korzytaliśmy:
y>=x => (pom (y::xs) x ≡ is_sorted y::xs)

1. Baza indukcji
y>=x => (pom (y::[]) x ≡ is_sorted y::[])
a) Jeżeli x<y to y>=x => (pom (y::[]) x ≡ is_sorted y::[]) spełniona.
b) Jeżeli y>=x
pom (y::[]) x
==
pom [y] x
==
pom [] y
==
true
==
pom [] y
==
pom [y] min_int
==
is_sorted [y]
==
is_sorted y::[]

2. Załóżmy, że dla dowolnego x,y,xs zachodzi:
y>=x => (pom (y::xs) x ≡ is_sorted y::xs)
i udowadnijmy, że dla dowolnego z zachodzi
y>=x => (pom (y::z::xs) x ≡ is_sorted y::z::xs)
a) Jeżeli x<y to y>=x => (pom (y::z::xs) x ≡ is_sorted y::z::xs) spełniona.
b) Jeżeli y>=x

1)Jeżeli z>=y
pom (y::z::xs) x
==
pom z::xs y
==
pom xs z
==
pom z::xs y
==
pom y::z::xs min_int
==
is_sorted y::z::xs

2) Jeżeli z<y
pom (y::z::xs) x
==
pom z::xs y
== 
false
==
pom z::xs y
==
pom y::z::xs min_int
==
is_sorted y::z::xs

I to kończy dowód lematu
Ciekawe jest to, że nie użyłem tezy indukcyjnej w dowodzie zatem można to było zrobić jawnie.








