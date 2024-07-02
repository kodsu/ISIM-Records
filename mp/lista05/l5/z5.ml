type 'v nnf =
  | NNFLit of bool * 'v
  | NNFConj of 'v nnf * 'v nnf
  | NNFDisj of 'v nnf * 'v nnf;;

let rec neg_nnf f = 
  match f with 
  |NNFLit(a,b) -> NNFLit(not a,b) 
  |NNFConj(a,b) -> NNFDisj(neg_nnf a,neg_nnf b) 
  |NNFDisj(a,b) -> NNFConj(neg_nnf a,neg_nnf b);;


let rec eval_nnf f v =
  match v with
  | NNFLit(a,b) -> if a==true then f b else not(f b) 
  | NNFConj(a,b) -> eval_nnf f a && eval_nnf f b 
  | NNFDisj(a,b) -> eval_nnf f a || eval_nnf f b;;
  

eval_nnf (
  fun x -> match x with 
    |"a" -> true 
    |"b" -> true
)
(NNFConj(NNFLit(true,"a"),NNFLit(false,"b")));;

Tw. eval_nnf w (neg_nnf b) ≡ not (eval_nnf w b)
1. Pokażę, że dla dowolnego wartościowania w i zmiennej a zachodzi
a) eval_nnf w (neg_nnf NNFLit(true,a)) ≡ not (eval_nnf w NNFLit(true,a))
b) eval_nnf w (neg_nnf NNFLit(false,a)) ≡ not (eval_nnf w NNFLit(false,a))


a) eval_nnf w (neg_nnf NNFLit(true,a))
==(def. neg_nnf i eval not)
eval_nnf w NNFLit(false,a)
==(def. eval_nnf)
not(w a)
==(def. eval_nnf)
not(eval_nnf w NNFLit(true,a))

b) eval_nnf w (neg_nnf NNFLit(false,a))
==(def. neg_nnf i eval not)
eval_nnf w NNFLit(true,a)
==(def. eval_nnf)
w a
==(zasada podwojnej negacji)
not (not w a)
==(def. eval_nnf)
not(eval_nnf w NNFLit(false,a))

2. Weźmy dowolne a,b. Załóżmy, że dla każdego w zachodzi 
eval_nnf w (neg_nnf a) ≡ not (eval_nnf w a) i
eval_nnf w (neg_nnf b) ≡ not (eval_nnf w b)
i udowdnijmy, że zachodzi
a) eval_nnf w (neg_nnf NNFConj(a,b)) ≡ not (eval_nnf w NNFConj(a,b))
b) eval_nnf w (neg_nnf NNFDisj(a,b)) ≡ not (eval_nnf w NNFDisj(a,b))

a) eval_nnf w (neg_nnf NNFConj(a,b))
==(def. neg_nnf)
eval_nnf w (NNFDisj(neg_nnf a,neg_nnf b))
==(def. eval_nnf)
eval_nnf w (neg_nnf a) || eval_nnf w (neg_nnf b)
==(zał. ind 2 razy)
not (eval_nnf w a) || not (eval_nnf w b)
==(logika)
not((eval_nnf w a) && (eval_nnf w b))
==(def. eval_nnf)
not(eval_nnf w NNFConj(a,b))

b) eval_nnf w (neg_nnf NNFDisj(a,b))
==(def. neg_nnf)
eval_nnf w (NNFConj(neg_nnf a,neg_nnf b))
==(def. eval_nnf)
eval_nnf w (neg_nnf a) && eval_nnf w (neg_nnf b)
==(zał. ind 2 razy)
not (eval_nnf w a) && not (eval_nnf w b)
==(logika)
not((eval_nnf w a) || (eval_nnf w b))
==(def. eval_nnf)
not(eval_nnf w NNFDisj(a,b))




