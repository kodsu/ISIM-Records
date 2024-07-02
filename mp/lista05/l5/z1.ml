let rec map f = function
  | [] -> []
  | x :: xs' -> f x :: map f xs';;


Tw. dla każdego f g xs zachodzi: map f (map g xs) ≡ map (fun x -> f (g x)) xs
Indukujemy się względem xs
1. Pokażę, że dla każdej f g: map f (map g []) ≡ map (fun x -> f (g x)) []
map f (map g []) 
==(def. map)
map f []
==(def. map)
[]
==(def. map)
map (fun x -> f (g x)) []

2.
Weźmy dowolne xs. Załóżmy, że dla każdego g, f 
   zachodzi map f (map g xs) ≡ map (fun x -> f (g x)) xs,
   pokażę, że dla każdego f, g, x
   zachodzi map f (map g x::xs) ≡ map (fun x -> f (g x)) x::xs
   
map f (map g x::xs)
==(def. map)
map f (g x :: map g xs)
==(def. map)
f g x :: map f (map g xs)
==(z zał. ind)
f g x :: map (fun x -> f (g x)) xs
==(z okamla)
(fun x -> f (g x)) x :: map (fun x -> f (g x)) xs
==(def. map)
map (fun x -> f (g x)) x :: xs


