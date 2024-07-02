type 'v nnf =
  | NNFLit of bool * 'v
  | NNFConj of 'v nnf * 'v nnf
  | NNFDisj of 'v nnf * 'v nnf;;

let rec neg_nnf f = 
  match f with 
  |NNFLit(a,b) -> NNFLit(not a,b) 
  |NNFConj(a,b) -> NNFDisj(neg_nnf a,neg_nnf b) 
  |NNFDisj(a,b) -> NNFConj(neg_nnf a,neg_nnf b);;

Tw. Dla dowolnego a : 'a nnf zachodzi neg_nnf (neg_nnf a) ≡ a
1. Pokażę, że dla dowolnego f : 'v zachodzi 
a) neg_nnf (neg_nnf P(NNFLit(false,f))) ≡ P(NNFLit(false,f)) i 
b) neg_nnf (neg_nnf P(NNFLit(true,f))) ≡ P(NNFLit(true,f))

a) neg_nnf (neg_nnf P(NNFLit(false,f)))
==(def neg_nnf)
neg_nnf P(NNFLit(true,f))
==(def neg_nnf)
P(NNFLit(false,f))

b) neg_nnf (neg_nnf P(NNFLit(true,f)))
==(def neg_nnf)
neg_nnf P(NNFLit(false,f))
==(def neg_nnf)
P(NNFLit(true,f))

2. Weźmy dowolne a,b. Załóżmy, że zachodzi neg_nnf (neg_nnf a) ≡ a i neg_nnf (neg_nnf b) ≡ b
pokażę, że zachodzi 
a) neg_nnf (neg_nnf (NNFConj(a,b))) ≡ (NNFConj(a,b))
b) neg_nnf (neg_nnf (NNFDisj(a,b))) ≡ (NNFDisj(a,b))

a) neg_nnf (neg_nnf (NNFConj(a,b)))
==(def. neg_nnf)
neg_nnf NNFDisj(neg_nnf a,neg_nnf b)
==(def. neg_nnf)
NNFConj(neg_nnf (neg_nnf a),neg_nnf (neg_nnf b))
==(2 razy założenie indukcyjne)
NNFConj(a,b)

b) neg_nnf (neg_nnf (NNFDisj(a,b)))
==(def. neg_nnf)
neg_nnf NNFConj(neg_nnf a,neg_nnf b)
==(def. neg_nnf)
NNFDisj(neg_nnf (neg_nnf a),neg_nnf (neg_nnf b))
==(2 razy założenie indukcyjne)
NNFDisj(a,b)


