let fold_left f xs beg= 
    let rec inner xs acc =  
      match xs with 
        | [] -> acc 
        | el::xs_ -> inner xs_ (f acc el)
    in  
  inner xs beg ;; 

let fold_left2 f a xs =
  let rec it xs acc =
    match xs with
    | [] -> acc
    | x :: xs' -> it xs' (f acc x)
  in it xs a ;; 

let new_sum xs = fold_left2 (+) 0 xs ;; 

  new_sum [1; 2; 3; 4];;  
  (*uwaga - po definicji kazdej funkcji nalezy wstawic srednik podwojny ;; *)
let suma xs = fold_left (+) xs 0;; 

suma [1; 2;3;-123349201];; 