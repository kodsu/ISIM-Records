(* zwraca pare (minimum, [lista xs]\minimum ) *)
exception EmptyListException

let rec select2 xs =   (* zmienia kolejnosc pozostalej czesci tablicy*)  
    match xs with  
      | [] -> raise EmptyListException
      | el :: [] -> (el, [])
      | el :: xs_ -> 
        let m,suf = select2 xs_ in 
          if m <= el 
            then (m, el::suf) 
            else (el, m::suf) 
;; 

let select xs =  
  let rec minimum ys =  
    match ys with 
      | [] -> raise EmptyListException 
      | el::[] -> el 
      | el::ys_ -> let mval = minimum ys_ 
                    in if el < mval then el else mval 
  in
  let rec usun ys el = 
    match ys with 
      | [] -> raise EmptyListException 
      | v :: ys_ -> 
        if v = el then ys_ else v :: (usun ys_ el) 
  in
  let min_val = minimum xs 
  in
  (min_val, (usun xs min_val)) 

let rec select_sort xs =   
  match xs with 
    | [] -> []  
    | xs_ -> 
        let el, suf = select xs_ in 
          el :: (select_sort suf)  
;; 
  
select [4; 3; 1; 2; 5];;
select_sort [1; 5; 0; 7; 1; 4; 1; 0];;

