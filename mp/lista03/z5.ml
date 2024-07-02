type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree ;; 

let rec insert_bst x (t: 'a tree) =  
  match t with 
  | Leaf -> Node(Leaf, x, Leaf) 
  | Node(lt, value, rt) -> if x < value  then Node(insert_bst x lt, value, rt)  
    else if x > value then Node(lt, value, insert_bst x rt) else Node(lt, value, rt) 
;;

let t = Node(Leaf, 2, Leaf);; 
let t = insert_bst 1 t;; 
let t = insert_bst 3 t;;

