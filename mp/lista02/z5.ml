let float_max (a: float) (b: float) = 
      if a < b then b else a 
;; 

let rec maximum xs  = 
  match xs with 
    | [] -> neg_infinity
    | el :: xs_ -> float_max (maximum xs_) el
;; 

(*tutaj konczy sie merytoryczna czesc zadania i zaczyna testing*)
print_float (maximum []) ;; print_newline();;
print_float (maximum [-3.; -2.; 1.; 0.]) ;; print_newline();;