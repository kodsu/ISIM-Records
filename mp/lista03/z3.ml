let build_list n f =   
  if n = 0 then [] 
  else 
    let rec inner k = 
      if k = n-1 then [f k] 
      else  (f k) :: inner (k+1) 
    in 
    inner 0 
  ;; 
let negatives n = build_list n (fun k -> -k-1);; 
negatives 5;; 
negatives 0;; 

let recirocals n = build_list n (fun k -> 1.0 /. (float_of_int(k+1)) );; 
recirocals 5;;

let evens n = build_list n (fun k -> 2*k);; 
evens 5;;

let identityM n = build_list n (fun k-> build_list n (fun m -> if m=k then 1 else 0 ));;  
identityM 2;; 
identityM 6;;