(* abstract syntax tree *)

type bop = Mult | Div | Add | Sub | Eq | Neq | Ge | Geq| Le | Leq | And | Or 

type expr =
  | Int of int
  | Bool of bool
  | Binop of bop * expr * expr
  | If of expr * expr * expr
                               
