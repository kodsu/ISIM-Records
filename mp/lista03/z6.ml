type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree ;; 

let rec insert_bst x (t: 'a tree) =  
  match t with 
  | Leaf -> Node(Leaf, x, Leaf) 
  | Node(lt, value, rt) -> if x < value  then Node(insert_bst x lt, value, rt)  
    else if x > value then Node(lt, value, insert_bst x rt) else Node(lt, value, rt) 
;;
let rec fold_tree f a t = (*wylicza wartosc jakiejs funkcji f trojargumentowej dla argumentow (a to wartosc z liscia) z drzewka wywolania bedacym drzewkiem t *)
  match t with
  | Leaf -> a
  | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r)




let some_tree =
  Node ( Node ( Leaf , 2, Leaf ) ,5,  Node (Node ( Leaf , 6, Leaf ), 8, Node ( Leaf , 9, Leaf ) ) ) ;; 

let tree_product t = fold_tree (fun a b c -> a*b*c) 1 t;; 
tree_product some_tree;;  
let tree_flip t = fold_tree(fun a b c -> Node(c, b, a)) Leaf t;;
tree_flip some_tree;; 

let tree_height t = fold_tree(fun a b c -> if a > c then a+1 else c+1) 1 t;; 
tree_height some_tree;;  

let min a b = 
  if a < b then a else b;; 
let max a b = 
  if a > b then a else b;;  

let tree_span t = fold_tree (fun a b c -> let (la, ra) = a in let (lc, rc) = c in ( min la (min lc b) , max rc (max ra b ) )  )  (Int.max_int, Int.min_int) t;;  

tree_span some_tree;;  

let preorder t = fold_tree(fun a b c -> [b] @ a @ c)  [] t;; 
preorder some_tree;; 


