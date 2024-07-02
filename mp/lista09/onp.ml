
type expr =
  | Int of int
  | Add of expr * expr
  | Mult of expr * expr
;;
let rec eval (e : expr ) : int =
  match e with
  | Int n -> n
  | Add (e1 , e2 ) -> (eval e1) + (eval e2)
  | Mult (e1 , e2 ) -> (eval e1) * (eval e2)
;; 
type rpn_cmd =
  | Push of int
  | RAdd
  | RMult
;;
type rpn = rpn_cmd list ;; 
let rec to_rpn (e : expr ) : rpn =
  match e with
  | Int n -> [ Push n]
  | Add (e1 , e2 ) -> to_rpn e1 @ to_rpn e2 @ [ RAdd ]
  | Mult (e1 , e2 ) -> to_rpn e1 @ to_rpn e2 @ [ RMult ]
;;
let rec eval_rpn (r : rpn ) (s : int list ) : int =
  match r , s with
  | [] , [n] -> n
  | Push n :: r', _ -> eval_rpn r' (n :: s)
  | RAdd :: r', n1 :: n2 :: s' -> eval_rpn r' ( n2 + n1 :: s')
  | RMult :: r', n1 :: n2 :: s' -> eval_rpn r' ( n2 * n1 :: s')
  | _ ,_ -> failwith " error !"
;;

let rec from_rpn (r : rpn) (s : expr list) : expr = 
    match r, s with  
    | Push v :: r', _ -> from_rpn r' ( Int (v) :: s) 
    | RAdd :: r', b :: a :: s' -> from_rpn r' ( Add(a, b) :: s') 
    | RMult :: r', b :: a :: s' -> from_rpn r' (Mult(a, b) :: s') 
    | [], [v] -> v 
    | _, _ -> failwith "error!" 
;;  

from_rpn [ Push(1); Push(2); RMult; Push(12); RAdd] [];; (* test from_rpn*)



let rec random_expr (mdep: int) : expr = 
  match mdep with
  | 1 -> Int(Random.int 1000) 
  | mdep -> ( 
    match Random.int 3 with  
    | 0 -> Int (Random.int 1000) 
    | 1 -> Add(random_expr (mdep-1), random_expr (mdep-1) )
    | 2 -> Mult(random_expr (mdep-1), random_expr (mdep-1) )  
    | _ -> failwith "error!"
  ) 
;; 

let rec test  (max_depth:int) (n:int) : bool = 
  if n == 0 then true else 
  let rexpr = random_expr max_depth in 
  (from_rpn (to_rpn rexpr) [] = rexpr) && (test max_depth (n-1)) 
  ;; 

let rec test_ce (max_depth:int) (n:int) : expr option = 
  if n == 0 then None else   
  let vale = (test_ce max_depth (n-1)) in
  if vale == None then 
    let rexpr = random_expr max_depth in 
    if (from_rpn (to_rpn rexpr) [] = rexpr) 
      then None 
    else Some rexpr 
  else  vale 
;; 