let rec fib n = 
    match n with
    | 0 -> 0
    | 1 -> 1 
    | n -> (fib (n-1)) + (fib (n -2) )
;; 

let rec fib_iter n = 
    let rec pf_iter k a b = 
        match k with 
        | 0 -> b 
        | k -> pf_iter (k-1) b (a + b)
    in 
    match n with 
    | 0 -> 0 
    | n -> pf_iter (n-1) 0 1
;;

print_int (fib_iter 0);; 
print_newline();; 
print_int (fib_iter 1);;     
print_newline();; 
print_int (fib_iter 20);;  
print_newline();;   
print_int (fib 20);;  
print_newline();
(*print_int (fib 0);; 
print_newline();; 
print_int (fib 1);;     
print_newline();  
print_int (fib 20);;  
print_newline(); *)