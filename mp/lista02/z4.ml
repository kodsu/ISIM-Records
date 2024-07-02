w
let rec mem x xs  = 
  match xs with 
    | [] -> false 
    | el :: xs_ -> (el = x) || (mem x xs_) 
;; 

(*tutaj konczy sie merytoryczna czesc zadania i zaczyna testing*)
print_string (string_of_bool(mem 2 [1; 2; 3]));; print_newline();;
print_string (string_of_bool(mem 4 [1; 2; 3]));; print_newline();; 