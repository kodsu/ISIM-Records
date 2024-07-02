open Ast

let parse (s : string) : expr =
  Parser.prog Lexer.read (Lexing.from_string s)

type value =
  | VInt of int
  | VBool of bool

let eval_op (op : bop) (v1 : value) (v2 : value) : value =
  match op, v1, v2 with
  | Add,  VInt i1, VInt i2 -> VInt (i1 + i2)
  | Sub,  VInt i1, VInt i2 -> VInt (i1 - i2)
  | Mult, VInt i1, VInt i2 -> VInt (i1 * i2)
  | Div,  VInt i1, VInt i2 -> VInt (i1 / i2)
  | Eq,   VInt i1, VInt i2 -> VBool (i1 = i2)
  | Lt,   VInt i1, VInt i2 -> VBool (i1 < i2)
  | Gt,   VInt i1, VInt i2 -> VBool (i1 > i2)
  | Leq,  VInt i1, VInt i2 -> VBool (i1 <= i2)
  | Geq,  VInt i1, VInt i2 -> VBool (i1 >= i2)
  | Neq,  VInt i1, VInt i2 -> VBool (i1 <> i2)
  | _ -> failwith "type error"

let expr_of_value (v : value) : expr = (*rzutuje wartosci na wyrazenia*)
  match v with
  | VInt a -> Int a
  | VBool a -> Bool a 

(* Evaluation via substitution *)

module Subst = struct

let rec subst (x : ident) (s : expr) (e : expr) : expr = (* podstawiamy za x wyrażenie s w wyrażeniu e*)
  match e with
  | Binop (op, e1, e2) -> Binop (op, subst x s e1, subst x s e2)
  | If (p, t, e) -> If (subst x s p, subst x s t, subst x s e)
  | Var y -> if x = y
               then s
               else e
  | Let (y, e1, e2) -> if x = y
                         then Let (y, subst x s e1, e2)
                         else Let (y, subst x s e1, subst x s e2) 
  | Sum(y,e1,e2,e3) -> Sum(y, subst x s e1, subst x s e2, subst x s e3)
  | _ -> e


let rec closed (e:expr) : bool = 
  match e with
  | Int _ -> true
  | Bool _ -> true
  | If (p, t, e) -> (closed p) && (closed t) && (closed e)
  | Binop (_, e1, e2) -> (closed e1) && (closed e2)
  | Let (x, e1, e2) -> (closed e1) && (closed (subst x e1 e2))
  | Var _ -> false  
  | Sum(x, el, er, ef) -> (closed el) && (closed er) && (closed (subst x el ef))


let int_of_value (x : value) = 
  match x with  
  | VInt x -> x 
  | VBool _ -> failwith "type error occurred" ;; 
let expr_of_int (x :int) = 
  (Int x) ;; 
let val_of_int (x:int)= 
  (VInt x);; 

let rec range_list (l:int) (r:int) = 
  if l = r then [r] 
      else  l :: (range_list (l+1) r) 

let rec eval (e : expr) : value =
  match e with
  | Int n -> VInt n
  | Bool b -> VBool b
  | If (p, t, e) ->
      (match eval p with
      | VBool true -> eval t
      | VBool false -> eval e
      | _ -> failwith "type error")
  | Binop (And, e1, e2) ->
      (match eval e1 with
      | VBool true -> eval e2
      | VBool false -> VBool false
      | _ -> failwith "type error")
  | Binop (Or, e1, e2) ->
      (match eval e1 with
      | VBool false -> eval e2
      | VBool true -> VBool true
      | _ -> failwith "type error")
  | Binop (op, e1, e2) -> eval_op op (eval e1) (eval e2)
  | Let (x, e1, e2) -> let s = expr_of_value (eval e1) in (* robimy experssion z wartosci e1 i podstawiamy do wartsoci za x expr(e1) w e2, to jest wartosc*)
                       eval (subst x s e2)
  | Sum (x, el, er, ef) -> if not (closed e) then failwith "unbound value in sum range" 
        else 
          val_of_int (List.fold_left (fun acc y -> acc + y) 0  
            ( List.map (fun y ->  int_of_value(eval (subst x (expr_of_int y) ef))  ) 
              (range_list (int_of_value(eval el)) (int_of_value(eval er)))   
            ) 
          )
  | Var x -> failwith ("unbound value " ^ x)

let interp (s : string) : value =
  eval (parse s)

end




(* Evaluation via environments *)

module Env = struct

module M = Map.Make(String)

type env = value M.t

type eenv = expr M.t

type senv = string M.t
let rec simplify (env:eenv) (ee:expr) :expr =  
  match ee with 
  | Int n -> Int n
  | Bool b -> Bool b
  | If (p, t, e) ->
      (match simplify env p with 
      | Bool true -> simplify env t 
      | Bool false -> simplify env e
      | _ -> If(p, t, e)
      )
  | Binop (And, e1, e2) -> 
      let e1s = simplify env e1 in 
      let e2s = simplify env e2 in 
      (match e1s,e2s with
      | Bool a, Bool b -> Bool (a && b) 
      | _,_ -> Binop(And, e1s, e2s) 
      )
  | Binop (Or, e1, e2) ->
      let e1s = simplify env e1 in 
      let e2s = simplify env e2 in 
      (match e1s,e2s with
      | Bool a, Bool b -> Bool (a || b) 
      | _,_ -> Binop(Or, e1s, e2s) 
      )
  | Binop (op, e1, e2) -> 
      let e1s = simplify env e1 in 
      let e2s = simplify env e2 in 
      (match e1s,e2s with
      | Int a, Int b ->  expr_of_value(eval_op op (VInt(a)) (VInt(b)) )
      | _,_ -> Binop(op, e1s, e2s) 
      )
  | Let (x, e1, e2) ->
      let r = simplify env e1 in 
      (match r with 
      | Bool _ -> let new_env = M.update x (fun _ -> Some r) env in simplify new_env e2 
      | Int _ -> let new_env = M.update x (fun _ -> Some r) env in simplify new_env e2  
      | _ -> Let(x, r, simplify env e2) 
      )
  | Var x ->
      (match M.find_opt x env with
      | Some v -> v
      | None -> Var x 
      )
  | Sum(_, _, _, _) -> failwith "not implemented yet" 
;;

let rec alpha_equ (e1:expr) (e2:expr) (env1:senv) (env2:senv): bool = 
  match e1,e2 with 
  | Int n,Int k -> n = k
  | Int _, _ -> false 
  | Bool b, Bool c -> b = c
  | Bool _, _ -> false 
  | If (p1, t1, f1), If(p2,t2,f2) -> 
      (alpha_equ p1 p2 env1 env2) && (alpha_equ t1 t2 env1 env2) && (alpha_equ f1 f2 env1 env2)  
  | If(_,_,_),_ -> false 
  | Binop (op1, a1, b1), Binop(op2, a2, b2) -> 
      (op1 = op2) && (alpha_equ a1 a2 env1 env2) && (alpha_equ b1 b2 env1 env2) 
  | Binop(_,_,_),_ -> false 
  | Let (x1, e1l, e1r),Let(x2, e2l, e2r) ->
      let env1_new = M.add x1 x2 env1 in 
      let env2_new = M.add x2 x1 env2 in 
      (alpha_equ e1l e2l env1 env2) && (alpha_equ e1r e2r env1_new env2_new) 
  | Let(_,_,_),_ -> false 
  | Var x, Var y ->
      (match M.find_opt x env1 with
      | Some xval -> 
          (match M.find_opt y env2 with 
            | Some yval -> (xval = y) && (yval = x) 
            | None -> false (*zmienna zwiazana i wolna*)
          ) 
      | None -> 
          (match M.find_opt y env2 with 
          | Some _ -> false (*zmienna wolna i zwiazana*) 
          | None -> true (*dwie zmienne wolne*)
          )
      )
  | Var _, _ -> false 
  | Sum(_, _, _, _), Sum(_,_,_,_) -> failwith "not implemented yet" 
  | Sum(_,_,_,_),_ -> false 
;; 



let rec grename_expr (e:expr) (env:senv) (path:string) = 
  match e with 
  | Int n -> Int n
  | Bool b -> Bool b
  | If (p, t, e) -> If(grename_expr p env (path^"A"), grename_expr t env (path^"B"), grename_expr e env (path^"C")) 
  | Binop (op, e1, e2) -> Binop(op, grename_expr e1 env (path^"D"), grename_expr e2 env (path^"E") )
  | Let (x, e1, e2) ->
      let new_env = M.add x path env
      in Let(path, grename_expr e1 env (path^"F"), grename_expr e2 new_env (path^"G")) 
  | Var x ->
      (match M.find_opt x env with
      | Some v -> Var v
      | None -> Var x 
      )
  | Sum(_, _, _, _) -> failwith "not implemented yet" 
;; 

let rename_expr (e:expr) = 
  grename_expr e (M.empty) "A";; 



let alpha_equiv (e1:expr) (e2:expr) = 
  alpha_equ e1 e2 M.empty M.empty 
;; 
(*do testingu: 
alpha_equiv (Binop(Add, Int(1), Var("x"))) (Binop(Add,Int(1), Var("y")));;

*)

let rec eval_env (env : env) (e : expr) : value =
  match e with
  | Int n -> VInt n
  | Bool b -> VBool b
  | If (p, t, e) ->
      (match eval_env env p with
      | VBool true -> eval_env env t
      | VBool false -> eval_env env e
      | _ -> failwith "type error")
  | Binop (And, e1, e2) ->
      (match eval_env env e1 with
      | VBool true -> eval_env env e2
      | VBool false -> VBool false
      | _ -> failwith "type error")
  | Binop (Or, e1, e2) ->
      (match eval_env env e1 with
      | VBool false -> eval_env env e2
      | VBool true -> VBool true
      | _ -> failwith "type error")
  | Binop (op, e1, e2) -> eval_op op (eval_env env e1) (eval_env env e2)
  | Let (x, e1, e2) ->
      let r = eval_env env e1 in
      let new_env = M.update x (fun _ -> Some r) env in
      eval_env new_env e2
  | Var x ->
      (match M.find_opt x env with
      | Some v -> v
      | None -> failwith ("unbound value" ^ x)) 
  | Sum(_, _, _, _) -> failwith "not implemented yet"
  ;;  
let git_cp (e:expr) = 
  simplify M.empty  e;; 
    

let eval : expr -> value = eval_env M.empty 

let interp (s : string) : value =
  eval (parse s) 
;; 

let parse_rename (s:string):expr = 
    rename_expr(parse s);; 
let parse_ziomo(s:string):expr = 
  parse(s) 
;; 
end

