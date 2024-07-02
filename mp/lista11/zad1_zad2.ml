(*let exists f xs = 
  List.fold_left ( fun b -> b || f x) false xs ;;  *)

let exists f xs = 
  List.fold_left ( fun b x -> b || f x) false xs ;; 


let exists_exc f xs =   
  let exception ResultFound in 
  let inner_exists f x = 
    List.fold_left(fun acc x -> if f x then raise ResultFound 
    else acc ) false xs in 
  try  
  inner_exists f xs  
  with 
  | ResultFound -> true 
;; 
(*exists (fun x -> x = 1) [1; 2; 3];;
exists (fun x -> x = 123) [12; 123; 1234];; 
exists (fun x -> x mod 5 = 0) [1; 2; 3; 4];;  
let x = 100001;; *)
(* 
    exists_exc (fun x -> x = 1) [1; 2; 3];;
    exists_exc (fun x -> x = 123) [12; 123; 1234];; 
    exists_exc (fun x -> x mod 5 = 0) [1; 2; 3; 4];;  
    exists_exc (fun x -> x = 25) [5; 125; 5];; 
*) 
(*exception Not_found *) 

(* to do: 
val find : ('a -> bool) -> 'a list -> 'a
find f l returns the first element of the list l that satisfies the predicate f.
Raises Not_found if there is no value that satisfies f in the list l.
*)
let find (type t) p (xs : t list) =  
  let exception Found of t in  
  let exc_find p xs = 
    List.fold_left (fun acc x -> if p x then raise (Found x) else 
      acc) None xs in  
  let opt_val = try  exc_find p xs  
  with 
    | Found x -> Some x 
    | _ ->  None 
  in match opt_val with 
  | Some v -> v 
  | None -> raise Not_found 
;; 

find (fun x -> x = 1) [1; 2; 3];;
find (fun x -> x = 123) [12; 123; 1234];; 
find (fun x -> x mod 5 = 0) [1; 2; 3; 4];;  
find (fun x -> x = 25) [5; 125; 5];; 









