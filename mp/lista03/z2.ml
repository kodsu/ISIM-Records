let compose f g x = 
    f(g x);; 
let inc x = x +1;;  
let square x = x*x;; 

compose square inc 5;; 
compose inc square 5;;