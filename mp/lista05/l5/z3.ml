type 'v nnf =
| NNFLit of bool * 'v
| NNFConj of 'v nnf * 'v nnf
| NNFDisj of 'v nnf * 'v nnf;;

Zasada indukcji dla formuł typu 'v nnf:
dla każdej własności P,
jeśli dla dowolnego a : 'v zachodzi P(NNFLit(true,a)) i P(NNFLit(false,a))
oraz dla każdego v,w : 'v nnf,

1. P(v) i P(w) implikuje 
P(NNFConj(v,w)) i P(NNFDisj(v,w))

to dla każdej formuły f zachodzi P(f)