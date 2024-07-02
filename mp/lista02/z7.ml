let rec is_sorted xs =  
    match xs with 
      | [] -> true
      | el :: [] ->  true
      | a :: b :: xs_ -> (a <= b) && (is_sorted (b::xs_) ) 
;; 

(*tutaj konczy sie merytoryczna czesc zadania i zaczyna testing*)

print_string (string_of_bool(is_sorted [3; 2; 3]));; print_newline();;
print_string (string_of_bool(is_sorted []));; print_newline();; 
print_string (string_of_bool(is_sorted [-9]));; print_newline();;  
print_string (string_of_bool(is_sorted [-9; -8; -9; 1; 1; 21]));; print_newline();; 