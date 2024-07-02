let rec suffixes xs =  
    match xs with 
      | [] -> [[]] 
      | el::xs_ -> (el::xs_) :: (suffixes xs_) 
;; 

(*tutaj konczy sie merytoryczna czesc zadania i zaczyna testing*)
(* 
nie umiem tego wypisac wiec zrobilem testa w utopie
  suffixes [1; 2; 3; 4];;
- : int list list = [[1; 2; 3; 4]; [2; 3; 4]; [3; 4]; [4]; []]
  
*)