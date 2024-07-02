Dla dowolnych f i g oraz xs zachodzi 
map f (map g xs) = map (fun x -> f (g x)) xs  

Teza: T(n) dla kazdej listy xs dlugosci <= n  zachodzi:  
    map f (map g xs) = map (fun x -> f (g x)) xs   

Baza indukcji T(0) -- dla listy pustej xs = [] 
map f (map g []) 
== (def. map)
 map f [] 
== (def. map)
 [] 
oraz 
map (fun x -> f (g x))  
== (def. map)
[] = [] 

Krok indukcji -- T(n) => T(n+1) 
Wystarczy pokazac, że jesli teza zachodzi dla pewnego xs, to zachodzi tez dla x::xs 

map f (map g x::xs) 
== (def. map) 
 map f ( g(x)::(map g xs)) 
== (def. map)
f(g(x))::(map f (map g xs)) 
== (z zał. ind)  
f(g x) :: (map (fun x -> f (g x)) xs) 
== (z okamla) 
map (fun x -> f(g x)) x::xs 


