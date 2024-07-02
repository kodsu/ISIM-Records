type ident = string

type qbf =
  | Top
  | Bot
  | Var of ident
  | Forall of ident * qbf
  | Exists of ident * qbf
  | Not of qbf
  | Conj of qbf * qbf
  | Disj of qbf * qbf

(* Zad 6. *)

let rec subst (x : ident) (s : qbf) (f : qbf) : qbf =
  failwith "not implemented"

let rec eval (f : qbf) : bool =
  failwith "not implemented"

(* Zad 7. *)
  
module M = Map.Make(String)

type env = bool M.t

let rec eval_env (env : env) (f : qbf) : bool =
  failwith "not implemented"

