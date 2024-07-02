type ident = string

type qbf =
| Top (* ⊤ *)
| Bot (* ⊥ *)
| Var of ident (* x *)
| Disj of qbf * qbf (* ∨ *)
| Conj of qbf * qbf (* ∧ *)
| Not of qbf (* ¬ *)
| Forall of ident * qbf (* ∀ *)
| Exists of ident * qbf (* ∃ *)

let rec subst (x: ident) (s:qbf) (f:qbf) :qbf = 
    match f with
    | Top -> Top 
    | Bot -> Bot 
    | Var(y) ->   if x = y then s else Var(y)
    | Disj(p,q) -> Disj(subst x s p, subst x s q) 
    | Conj(p,q) -> Conj(subst x s p, subst x s q) 
    | Not(a)-> Not(subst x s a) 
    | Forall(y, sta) -> Forall(y, subst x s sta) 
    | Exists(y, sta) -> Exists(y, subst x s sta)

exception Var_eval_Exception
let rec eval (f : qbf) : bool = 
  match f with 
  | Top -> true 
  | Bot -> false 
  | Var(ident) -> raise Var_eval_Exception 
  | Disj(p,q) -> (eval p) || (eval q) 
  | Conj(p,q) -> (eval p) && (eval q) 
  | Not(a) -> not(eval a) 
  | Forall(y, sta) -> (eval (subst y Top sta)) && (eval (subst y Bot sta)) 
  | Exists(y, sta) -> (eval (subst y Top sta)) || (eval (subst y Bot sta)) 

(*test inputs:  
eval (Disj(Top, Bot));;
eval (Disj(Bot, Bot));;
eval (Exists("x",Var("x")));;
eval (Forall("x", Disj(Var("x"),Not(Var("x")))));;
*)


(* Sprawdzenie czy klucz jest w mapie 
  let czy_klucz_w_mapie = M.mem klucz map
Pobranie wartości przypisanej do danego klucza 
  let wartosc = M.find klucz map
Dodawanie wartości do mapy 
  let map_po_dodaniu = M.add "klucz" wartosc map
Zmiana wartości w mapie 
  let map_po_zmianie = M.add "klucz" nowa_wartosc map
Usuwanie wartości z mapy 
  let map_po_usunieciu = M.remove "klucz" map *)
open Stdlib
module M = Map.Make(String);;  
type env = bool M.t;; 
let rec eval_env (env: env) (f:qbf) : bool  = 
  match f with 
  | Top -> true 
  | Bot -> false 
  | Var(x) ->  
    ( match M.find_opt x env with 
      | Some v -> v 
      | None -> failwith("unbound value " ^ x)
    ) 
  | Disj(p,q) -> (eval_env env p) || (eval_env env q) 
  | Conj(p,q) -> (eval_env env p) && (eval_env env q) 
  | Not(a) -> not(eval_env env a) 
  | Forall(y, sta) ->  
      let new_env_top = M.add y true env in  
      let new_env_bot = M.add y false env in 
    (eval_env new_env_bot sta) && (eval_env new_env_top sta)
    (*(eval (subst y Top sta)) && (eval (subst y Bot sta))  *)
  | Exists(y, sta) -> 
      let new_env_top = M.add y true env in  
      let new_env_bot = M.add y false env in 
    (eval_env new_env_bot sta) || (eval_env new_env_top sta)
  ;; 
let eval_zero_env (f:qbf) = 
  let zero_env = M.empty  in 
  eval_env zero_env f ;; 
