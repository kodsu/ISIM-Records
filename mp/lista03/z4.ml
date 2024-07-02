let empty_set x = false;; 

let singleton a x = (x =a);;

let in_set x s = 
    let rec inner xs = 
      match xs with 
      | [] -> false 
      | el::xs_ -> (el=x) || inner xs_ 
    in 
  inner s;; 

let union s t x = 
  (s x) || (t x);; 

let intersect s t x = 
  (s x) && (t x);; 

  



