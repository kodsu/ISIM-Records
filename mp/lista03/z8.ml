type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree ;; 

let rec fold_tree f a t = (*wylicza wartosc jakiejs funkcji f trojargumentowej dla argumentow (a to wartosc z liscia) z drzewka wywolania bedacym drzewkiem t *)
  match t with
  | Leaf -> a
  | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r)

(* chcemy naklepac sobie to samo tyle ze w lepszej zlozonosci *)

let rec flat_append t xs = 
  match t with 
  | Leaf -> xs 
  | Node(lt, v, rt) ->   flat_append lt (v::(flat_append rt xs)) 
;;

let flatten t = flat_append t [];; 
let some_tree =
  Node ( Node ( Leaf , 2, Leaf ) ,5,  Node (Node ( Leaf , 6, Leaf ), 8, Node ( Leaf , 9, Leaf ) ) ) ;; 

let rec insert_bst x (t: 'a tree) =  
  match t with 
  | Leaf -> Node(Leaf, x, Leaf) 
  | Node(lt, value, rt) -> if x < value  then Node(insert_bst x lt, value, rt)  
    else Node(lt, value, insert_bst x rt) 
;;

let tree_sort xs = 
  let rec insert_rec xs t = 
    match xs with
    | [] -> t
    | el::xs_ -> insert_rec xs_ (insert_bst el t) 
  in  
  flatten (insert_rec xs Leaf );; 
tree_sort [2; 1; 3; -12; -23432; 324; 95032; -234; -234; -234; 0; 7; 123; 2342; 42309842423];;

(*flatten some_tree ;; *)

