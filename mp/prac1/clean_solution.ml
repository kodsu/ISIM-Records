
let (let*) xs ys = List.concat_map ys xs ;;   

type nonogram_spec = { rows : int list list ; cols : int list list } 

(*dla specyfikacji i dlugosci zwraca liste rozwiazan ktore je spelniaja*)
(*specyfikacja wierszy z lewej do prawej*)
(*specyfikacja kolumn od góry do dołu *)

let verify_row (spec:int list) (candidate: bool list)= 
  let rec read_list (xs : bool list) =
    match xs with 
    | [] -> [] 
    | [true] -> [1] 
    | [false] -> [0] 
    | false::xs_ -> (match read_list xs_ with  
                | [] -> [-1] 
                | 0:: xs__ -> 0::xs__ 
                | r:: xs__ -> 0::(r::xs__)  )
    | true::xs_ -> (match read_list xs_ with  
                | [] -> [-1]
                | r:: xs__ -> (r+1)::xs__ )
  in
  let normalize (xs: int list) = (*deleting leading zero from read list output*)
    match  xs with 
    | 0::xs_ -> xs_
    | xs -> xs
  in 
  normalize(read_list candidate) = spec;; 

(* da sie szybciej *)
let build_row (spec: int list) (m : int) = 
  let rec generate_lists (len : int) = 
    if len == 1 then [[false]; [true]] else 
      List.concat_map (fun x -> [false::x; true::x]) (generate_lists (len-1)) 
  in
  List.filter (fun x-> verify_row spec x ) (generate_lists m) ;; 

let rec intlist_of_boollist xs = (*pomocnicza funkcja do debugu*)
  match xs with 
  | [] -> [] 
  | false::xs_ -> 0::(intlist_of_boollist xs_) 
  | true::xs_ -> 1::(intlist_of_boollist xs_ )  
;;

let build_candidate (data:int list list) (m:int) = (*lista list poprawnych kombinacji wierszy roziwazujacych zagadke*) 
  let rec extend small big = (*funkcja, ktora przyjmuje dwie listy -- small i big 
     i zwraca liste obiektow bedacych postaci x::y, gdzie x \in small, y \in big*) 
    match small with 
    | [] -> [] 
    | s::sm_ -> (List.map (fun x-> s::x) big) @ (extend sm_ big ) 
  in 
  let rec solve_loc add = 
    match add with 
    | [] -> [[]] 
    | el::add_ -> extend el (solve_loc add_) 
  in 
  solve_loc (List.map (fun x -> build_row x m) data) ;; 

exception ErrorException
let verify_rows (spec:int list list) (cand:bool list list) =  
  if List.length spec <> List.length cand then raise ErrorException 
  else   
  let rec check_corr sl cl = 
    if sl = [] then true 
    else  
      (verify_row (List.hd sl) (List.hd cl)) && check_corr (List.tl sl) (List.tl cl) 
    in 
    check_corr spec cand;;  

(* verify_rows [[1]; [2]] [[false; true]; [true; true]];;
verify_rows [[1]; [2]] [[false; true]; [false; true]];; 
build_candidate [[]; [1]] 2;;  *)


let transpose (tab: 'a list list) =
  (*let n = List.length tab in *)
  let m = List.length (List.hd tab) in  
  let rec add sm big = (* funkcja ktora dla sm dlugosci k i biga dlugosci k (k list) sprawia 
     ze wrzucam na poczatek kazdej z list z big na poczatek k-ty element ze smalla*)
     match sm with 
     | [] -> [] 
     | s::sm_ -> if big = [] then raise ErrorException else (s:: (List.hd big))::(add sm_ (List.tl big)) 
  in
  let rec buildm_emp (v:int) =
      match v with  
      | 0 -> [] 
      | v -> []::(buildm_emp (v-1)) 
  in 
  let rec create blist =  
    if blist = [] then buildm_emp m 
    else 
        add (List.hd blist) (create (List.tl blist) )   
  in
  create tab;; 


let solve_nonogram (nono:nonogram_spec) =
  build_candidate ( nono.rows ) ( List.length (nono.cols))
  |> List.filter ( fun xss -> transpose xss |> verify_rows nono.cols ) ;; 
transpose [[1; 2; 3; 4; 5; 6]] ;;  



(* List.map (fun x-> intlist_of_boollist x) (build_row [1;2;3]10);;  *)
