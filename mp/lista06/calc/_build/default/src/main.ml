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
  | Neq,  VInt i1, VInt i2 -> VBool (i1 <> i2)
  | Ge,   VInt i1, VInt i2 -> VBool (i1 > i2)
  | Geq,  VInt i1, VInt i2 -> VBool (i1 >= i2)
  | Le,   VInt i1, VInt i2 -> VBool (i1 < i2)
  | Leq,  VInt i1, VInt i2 -> VBool (i1 <= i2) 
  | Or ,VBool b1, VBool b2 -> VBool (if b1  then true else b2 )
  | And,VBool b1, VBool b2 -> VBool (if b1 = false then false else b1 && b2)
  | _ -> failwith "type error"

let rec eval (e : expr) : value =
  match e with
  | Int n -> VInt n
  | Bool b -> VBool b
  | If (p, t, e) ->
      (match eval p with
      | VBool true -> eval t
      | VBool false -> eval e
      | _ -> failwith "type error") 
  | Binop (op, e1, e2) -> 
      (match op with  
      | And -> if (eval e1) = (VBool false) then (VBool false) else eval e2 
      | Or ->  if (eval e1) = (VBool true) then (VBool true) else eval e2
      |op -> eval_op op (eval e1) (eval e2) )
    

let interp (s : string) : value =
  eval (parse s)

