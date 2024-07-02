type 'a tree = Leaf | Node of 'a tree * 'a * 'a tree ;; 

let some_tree =
  Node ( Node ( Leaf , 2, Leaf ) ,5,  Node (Node ( Leaf , 6, Leaf ), 8, Node ( Leaf , 9, Leaf ) ) ) ;; 

(*usuwanie wierzchołka z bst*)
exception GlupiaSprawa;; 
let delete x t =  
  let rec subtree_min st =   
    match st with   
    | Leaf -> Int.max_int 
    | Node(lt, v, rt) -> min (subtree_min lt ) (min v (subtree_min rt) )
  in 
    let rec remove_val x st  =  
      match st with 
        | Leaf -> Leaf 
        | Node(lt, v, rt) -> if x < v then Node(remove_val x lt, v, rt) 
          else if x > v then Node(lt, v, remove_val x rt) else 
          match st with
            | Node (Leaf, v, Leaf) -> Leaf 
            | Node(Leaf, v, rt) -> rt 
            | Node(lt, v, Leaf) -> lt 
            | Node(lt, v, rt) -> let guy = subtree_min rt in Node(lt, guy, remove_val guy rt) 
            | Leaf -> raise GlupiaSprawa
  in
    remove_val x t ;; 

delete 2 some_tree;; 