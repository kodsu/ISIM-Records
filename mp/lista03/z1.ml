let fold_left f xs beg= 
    let rec inner xs acc =  
      match xs with 
        | [] -> acc 
        | el::xs_ -> inner xs_ (f acc el)
    in  
  inner xs beg ;;  

let product xs = fold_left (fun a b -> a*b) xs 1;;

product [1; 3; 4];;  
product[-1; -1; 21; 35];;