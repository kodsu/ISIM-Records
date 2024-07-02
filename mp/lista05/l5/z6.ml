type 'v formula =
| Var of 'v
| Neg of 'v formula
| Conj of 'v formula * 'v formula
| Disj of 'v formula * 'v formula;;

type 'v nnf =
  | NNFLit of bool * 'v
  | NNFConj of 'v nnf * 'v nnf
  | NNFDisj of 'v nnf * 'v nnf;;


let rec eval_nnf f v =
  match v with
  | NNFLit(a,b) -> if a==true then f b else not(f b) 
  | NNFConj(a,b) -> eval_nnf f a && eval_nnf f b 
  | NNFDisj(a,b) -> eval_nnf f a || eval_nnf f b;;
    
  
(* eval_nnf (
    fun x -> match x with 
      |"a" -> true 
      |"b" -> true
  )
  (NNFConj(NNFLit(true,"a"),NNFLit(false,"b")));; *)


let to_nnf f =
  let rec pom f truth =
    match f with
    | Var(v) -> NNFLit(truth,v)
    | Neg(v) -> pom v (not truth)
    | Conj(a,b) -> if truth == true then NNFConj(pom a true,pom b true) else NNFDisj(pom a false,pom b false)
    | Disj(a,b) -> if truth == true then NNFDisj(pom a true,pom b true) else NNFConj(pom a false,pom b false)
  in pom f true;;


to_nnf (Neg(Neg(Neg(Var("v")))));;
(* NNFLit (false, "v") *)

to_nnf (Neg(Conj(Disj(Var("a"),Neg(Var("b"))),Var("c"))));;
(* NFDisj (NNFConj (NNFLit (false, "a"), NNFLit (true, "b")), NNFLit (false, "c")) *)