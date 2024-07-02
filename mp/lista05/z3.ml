type 'v nnf =
| NNFLit of bool * 'v
| NNFConj of 'v nnf * 'v nnf
| NNFDisj of 'v nnf * 'v nnf 

Zasada indukcji dla formuł typu 'v: 
dla każdej własności W
jeśli 
1. 
Dla dowolnego a : 'v zachodzi W(NNFLit(true, a)) oraz 
W(NNFLit(false,a)) 


W(a) ^ W(b) => W(NNFConj (a,b) )
W(a) ^ W(b) => W(NNFDisj (a,b) )
to dla każdej formuły f zachodzi P(f) 