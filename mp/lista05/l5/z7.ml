type 'v formula =
| Var of 'v
| Neg of 'v formula
| Conj of 'v formula * 'v formula
| Disj of 'v formula * 'v formula;;

type 'v nnf =
  | NNFLit of bool * 'v
  | NNFConj of 'v nnf * 'v nnf
  | NNFDisj of 'v nnf * 'v nnf;;

let rec eval_formula f v = 
  match v with
  | Var(w) -> f w
  | Neg(w) ->  not (eval_formula f w)
  | Conj(a,b) -> (eval_formula f a) && (eval_formula f b)
  | Disj(a,b) -> (eval_formula f a) || (eval_formula f b);;

let to_nnf f =
  let rec pom f truth =
    match f with
    | Var(v) -> NNFLit(truth,v)
    | Neg(v) -> pom v (not truth)
    | Conj(a,b) -> if truth == true then NNFConj(pom a true,pom b true) else NNFDisj(pom a false,pom b false)
    | Disj(a,b) -> if truth == true then NNFDisj(pom a true,pom b true) else NNFConj(pom a false,pom b false)
  in pom f true;;

let rec eval_nnf f v =
  match v with
  | NNFLit(a,b) -> if a==true then f b else not(f b) 
  | NNFConj(a,b) -> eval_nnf f a && eval_nnf f b 
  | NNFDisj(a,b) -> eval_nnf f a || eval_nnf f b;;

eval_formula (
  fun x-> match x with
  |"a" -> false
)
(Neg(Neg(Neg(Var("a")))));;

eval_formula (
  fun x-> match x with
  |"a" -> true
  |"b" -> true
  |"c" -> false
)
(Neg(Conj(Disj(Var("a"),Neg(Var("b"))),Var("c"))));;

Zasada indukcji dla formuł typu 'v formula:
dla każdej własności P,
jeśli dla dowolnego a : 'v zachodzi P(Var(a))
oraz dla każdego v,w : 'v formula,

1. P(v) i P(w) implikuje 
P(Conj(v,w)) i P(Disj(v,w))
2. P(v) implikuje P(Neg(v))

to dla każdej formuły f zachodzi P(f)

!!!Lemat: eval_nnf f (pom a false) == not(eval_nnf f (pom a true))






Tw. eval_nnf f (to_nnf b) ≡ eval_formula f b
1. Pokażę, że dla dowolnego wartościowania f zachodzi: eval_nnf f (to_nnf Var(b)) ≡ eval_formula f Var(b)
eval_nnf f (to_nnf Var(b))
==(def. to_nnf)
eval_nnf f (pom Var(b) true)
==(def. pom)
eval_nnf f NNFLit(true,b)
==(def. eval_nnf)
f b
==(def. eval_formula)
eval_formula f Var(b)

2. Weźmy dowolne wartościowanie f i dowolną formułę a. 
Załóżmy, że zachodzi eval_nnf f (to_nnf a) ≡ eval_formula f a
i udowdnijmy, że zachodzi: eval_nnf f (to_nnf Neg(a)) ≡ eval_formula f Neg(a)

eval_nnf f (to_nnf Neg(a))
==(def. to_nnf)
eval_nnf f (pom Neg(a) true)
==(def. pom)
eval_nnf f (pom a false)
==Lemat
not(eval_nnf f (pom a true))
==
not(eval_nnf f (to_nnf a))
==
not(eval_formula f a)
==(def. eval_formula)
eval_formula f Neg(a)

3. Weźmy dowolne wartościowanie f i dowolne formuły a,b. 
Załóżmy, że zachodzi 
eval_nnf f (to_nnf a) ≡ eval_formula f a
eval_nnf f (to_nnf b) ≡ eval_formula f b
i udowdnijmy, że zachodzi: 
a) eval_nnf f (to_nnf Conj(a,b)) ≡ eval_formula f Conj(a,b)
b) eval_nnf f (to_nnf Disj(a,b)) ≡ eval_formula f Disj(a,b)


a) eval_nnf f (to_nnf Conj(a,b))
==(def to_nnf)
eval_nnf f (pom Conj(a,b) true)
==(def. pom)
eval_nnf f NNFConj(pom a true,pom b true)
==(def. to_nnf)
eval_nnf f NNFConj(to_nnf a,to_nnf b)
==(def. eval_nnf)
eval_nnf f (to_nnf a) && eval_nnf f (to_nnf b)
==(zał. ind)
eval_formula f a && eval_formula f b
==(def. eval_formula)
eval_formula f Conj(a,b)

b) eval_nnf f (to_nnf Disj(a,b))
==(def to_nnf)
eval_nnf f (pom Disj(a,b) true)
==(def. pom)
eval_nnf f NNFDisj(pom a true,pom b true)
==(def. to_nnf)
eval_nnf f NNFDisj(to_nnf a,to_nnf b)
==(def. eval_nnf)
eval_nnf f (to_nnf a) || eval_nnf f (to_nnf b)
==(zał. ind)
eval_formula f a || eval_formula f b
==(def. eval_formula)
eval_formula f Disj(a,b)



Pozostaje nam udowdnienie lematu którego użyliśmy:
Lemat: eval_nnf f (pom a false) == not(eval_nnf f (pom a true))

1. Pokażę, że dla dowolnego wartościowania f zachodzi:
eval_nnf f (pom Var(a) false) == not(eval_nnf f (pom Var(a) true))

eval_nnf f (pom Var(a) false)
==(def. pom)
eval_nnf f NNFLit(false, a)
==(def. eval_nnf)
not(f a)
==(def. eval_nnf)
not(eval_nnf f NNFLit(true,a))
==(def. pom)
not(eval_nnf f (pom Var(a) true))

2. Weźmy dowolne wartościowanie f i dowolną formułę a. 
Załóżmy, że zachodzi eval_nnf f (pom a false) == not(eval_nnf f (pom a true))
i udowdnijmy, że zachodzi: eval_nnf f (pom Neg(a) false) == not(eval_nnf f (pom Neg(a) true))

eval_nnf f (pom Neg(a) false)
==(def. pom)
eval_nnf f (pom a true)
==(podwojne zaprzeczenie)
not(not(eval_nnf f (pom a true)))
==(zał. ind.)
not(eval_nnf f (pom a false))
==(def. pom)
not(eval_nnf f (pom Neg(a) true))


3. Weźmy dowolne wartościowanie f i dowolne formuły a,b. 
Załóżmy, że zachodzi 
eval_nnf f (pom a false) == not(eval_nnf f (pom a true))
eval_nnf f (pom b false) == not(eval_nnf f (pom b true))
i udowdnijmy, że zachodzi: 
a) eval_nnf f (pom Conj(a,b) false) == not(eval_nnf f (pom Conj(a,b) true))
b) eval_nnf f (pom Disj(a,b) false) == not(eval_nnf f (pom Disj(a,b) true))

a)
eval_nnf f (pom Conj(a,b) false)
==(def. pom)
eval_nnf f NNFDisj(pom a false,pom b false)
==(def. eval_nnf)
eval_nnf f (pom a false) || eval_nnf f (pom b false)
==(2 razy zał. ind)
not(eval_nnf f (pom a true)) || not(eval_nnf f (pom b true))
==(podwojne zaprzeczenie)
not(not(not(eval_nnf f (pom a true)) || not(eval_nnf f (pom b true))))
==(zaprzeczenie dysjunkcji)
not((eval_nnf f (pom a true)) && (eval_nnf f (pom b true)))
==(def. eval_nnf)
not(eval_nnf f NNFConj(pom a true, pom b true))
==(def. pom)
not(eval_nnf f (pom Conj(a,b) true))

b)
eval_nnf f (pom Disj(a,b) false)
==(def. pom)
eval_nnf f NNFConj(pom a false,pom b false)
==(def. eval_nnf)
eval_nnf f (pom a false) && eval_nnf f (pom b false)
==(2 razy zał. ind)
not(eval_nnf f (pom a true)) && not(eval_nnf f (pom b true))
==(podwojne zaprzeczenie)
not(not(not(eval_nnf f (pom a true)) && not(eval_nnf f (pom b true))))
==(zaprzeczenie koniunkcji)
not((eval_nnf f (pom a true)) || (eval_nnf f (pom b true)))
==(def. eval_nnf)
not(eval_nnf f NNFDisj(pom a true, pom b true))
==(def. pom)
not(eval_nnf f (pom Disj(a,b) true))






