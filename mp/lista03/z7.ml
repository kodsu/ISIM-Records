type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree ;; 

let rec fold_tree f a t = (*wylicza wartosc jakiejs funkcji f trojargumentowej dla argumentow (a to wartosc z liscia) z drzewka wywolania bedacym drzewkiem t *)
  match t with
  | Leaf -> a
  | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r)

let flatten_slow t = fold_tree (fun l v r -> l @ [v] @ r) [] t;;  (* hehe beka, euler tour*)

(* chcemy naklepac sobie to samo tyle ze w lepszej zlozonosci *)

let rec flat_append t xs = 
  match t with 
  | Leaf -> xs 
  | Node(lt, v, rt) ->   flat_append lt (v::(flat_append rt xs)) 
;;

let flatten t = flat_append t [];; 
let some_tree =
  Node ( Node ( Leaf , 2, Leaf ) ,5,  Node (Node ( Leaf , 6, Leaf ), 8, Node ( Leaf , 9, Leaf ) ) ) ;; 

flatten some_tree ;; 

