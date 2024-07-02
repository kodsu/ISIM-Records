exception EmptyListError 

let split xs = 
  let rec list_length ys = 
    match ys with  
      | [] -> 0 
      | el::ys_ -> 1 + (list_length ys_) 
  in 
  let rec pref_split_list (n: int) ys = 
    match n with 
    | 0 -> ([], ys)
    | n -> match ys with 
              | [] ->  raise EmptyListError 
              | el :: ys_ -> 
                  let pocz, kon = pref_split_list (n-1) ys_ 
                  in el::pocz, kon 
  in
  let siz = list_length xs  
  in pref_split_list (siz/2) xs  
;; 

let rec merge xs ys = 
  match xs with 
   | [] -> ys 
   | xel :: xs_ -> 
      match ys with  
        | [] -> xel :: xs_  
        | yel :: ys_ -> 
          if xel <= yel 
            then xel :: (merge xs_ (yel :: ys_)) 
            else yel :: (merge (xel::xs_) ys_)  
;; 

let rec merge_sort xs = 
  match xs with  
    | [] -> [] 
    | el :: [] -> el ::[] 
    | xs ->  
        let a, b = split xs in
          merge (merge_sort a) (merge_sort b) 
;; 

merge_sort [1; 23; 43; 234; -92; -23453; -123; 0; 0; 0; -23; 23; 1239; 8432; 32411];;
