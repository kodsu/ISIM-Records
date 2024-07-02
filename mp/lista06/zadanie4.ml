let convert (nap : string) = 
  List.of_seq ( String.to_seq nap );; 
exception ErrorException
let parens_ok (nap: string) = 
  let rec stack_ani (cand : char list) (last:char list) = 
    if cand = [] then last else 
    if last = [] then stack_ani (List.tl cand) [List.hd cand] else 
    if (List.hd cand) == ')' && (List.hd last) == '(' then  stack_ani (List.tl cand) (List.tl last) 
    else  stack_ani (List.tl cand) ((List.hd cand)::last) 
  in 
  stack_ani (convert nap) [] == [] ;; 

(*testing: *)
parens_ok "(())";;  
parens_ok "";; 
parens_ok "(";; 
parens_ok "()(()))";;
let dziab = "   ";;
parens_ok "(())()" ;;
parens_ok "()())" ;;
parens_ok "((())" ;;
parens_ok "(x)" ;;