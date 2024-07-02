teściory: 
Binop (Add,
Binop (Mult, Var "x", Var "x"),
Binop (Mult, Var "x", Var "x"))


Binop (Add,
 Binop (Mult, Var "x", Int 10),
 Let ("x", Int 3,
  Binop (Mult, Var "x", Int 10)))


Binop (Add,
 Binop (Mult, Int 2, Var "x"),
 Binop (Add, Int 1,
  Binop (Mult, Int 2, Var "x")))

  If
 (Binop (Gt,
   Binop (Add, Var "x", Var "y"),
   Int 0),
 Binop (Add, Var "x", Var "y"), Int 0)

 let v1 = Binop (Add,
Binop (Mult, Var "x", Var "x"),
Binop (Mult, Var "x", Var "x")) ;; 
let v2 = Binop (Add,
Binop (Mult, Var "x", Int 10),
Let ("x", Int 3,
 Binop (Mult, Var "x", Int 10)));;  
let v3 = Binop (Add,
Binop (Mult, Int 2, Var "x"),
Binop (Add, Int 1,
 Binop (Mult, Int 2, Var "x")));; 

let v4 =   If
(Binop (Gt,
  Binop (Add, Var "x", Var "y"),
  Int 0),
Binop (Add, Var "x", Var "y"), Int 0);; 

let dmap = data_to_list (occ_map v4 M.empty);; 
cse v4;; 
