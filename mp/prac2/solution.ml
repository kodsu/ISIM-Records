(*Rozwiązanie pracowni 2 z MP 2024 *)
(*Jakub Szydło, 344760*) 
(*kod z dodanym komentarzem, z poprawioną przejrzystością względem wcześniejszych wersji*)
type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq

type ident = string

type expr =
  | Int of int
  | Bool of bool
  | Binop of bop * expr * expr
  | If of expr * expr * expr
  | Var of ident
  | Let of ident * expr * expr

module M = Map.Make(String)
type intmap = int M.t  (*typ mapy o kluczach typu string i wartościach typu int*)
type strmap = string M.t (*typ mapy o wartościach i kluczach typu string*)

module ExprMap = Map.Make(struct 
  type t = expr
  let compare = compare
end)

type histogram = int ExprMap.t  (* typ mapy o wartościach typu expr i kluczach typu int, będziemy ten typ wykorzystywać do przechowywania histogramu wystąpień
   podwyrażeń*)

let rename_expr (e : expr) : expr = (*zmienia nazwy wszystkich zmiennych 
zwiazanych na unikatowe, niemogace wystepowac jako nazwy zmiennych, gdyż wywolujemy to od napisu "#" 
a nazwy zmiennych moga zawierac w jezyku LET jedynie litery i cyfry, więc nasze oznaczenia muszą być inne niż nazwa jakiejkolwiek zmiennej, 
zamiana jest deterministyczna, więc dla a-równoważnych wyrażeń zwróci równe wyrażenia*)
  let rec grename_expr (e:expr) (env:strmap) (path:string) : expr = 
    match e with 
    | Int n -> Int n
    | Bool b -> Bool b
    | If (p, t, e) -> If(grename_expr p env (path ^ "A"), grename_expr t env (path ^ "B"), grename_expr e env (path ^ "C")) 
    | Binop (op, e1, e2) -> Binop(op, grename_expr e1 env (path ^ "D"), grename_expr e2 env (path ^ "E") )
    | Let (x, e1, e2) ->
        let new_env = M.add x path env
        in Let(path, grename_expr e1 env (path ^ "F"), grename_expr e2 new_env (path ^ "G")) 
    | Var x ->
        (match M.find_opt x env with
        | Some v -> Var v
        | None -> Var x 
        ) 
  in grename_expr e (M.empty) "#"

let merge_hist (h1 : histogram) (h2 : histogram) : histogram = (*dodawianie do siebie dwoch map bedacych "histogramami" 
   wartość dla danego klucza w mapie wynikowej, to suma wartości dla klucza w mapach-argumentach*)
  let merge_key _ v1 v2 =
    match v1, v2 with
    | Some x, Some y -> Some (x + y)
    | Some x, None -> Some x
    | None, Some y -> Some y
    | None, None -> None
  in
  ExprMap.merge merge_key h1 h2 

let hist_inc (e : expr) (h : histogram) : histogram = (*dodanie jednego elementu e do histogramu, jeśli e nie występuje w mapie, przypisujemy jemu 1*)
  match ExprMap.find_opt e h with  
  | Some x ->  ExprMap.add e (x + 1) h
  | None -> ExprMap.add e 1 h
    

let rec not_contain (e : expr) (m : intmap) : bool = (*czy wyrazenie nie zawiera zmiennych z m *)
  match e with
  | Int _ -> true
  | Bool _ -> true
  | If (p, t, e1) -> (not_contain p m) && (not_contain t m) && (not_contain e1 m )
  | Binop (_, e1, e2) -> (not_contain e1 m ) && (not_contain e2 m)
  | Let (x, e1, e2) -> (not_contain e1 m) && (not_contain e2 m)
  | Var x -> ( 
      match M.find_opt x m with
      | Some _ -> false 
      | None -> true
    ) 

let rec build_hist (e : expr) (m : intmap) : histogram = (*zwraca mapę podywrażeń (histogram) nie zawierajacych zmiennych wolnych
   bedacych zmiennymi zwiazanymi na wyzszym poizomie, tzn nie zajdzie sytuacja, że zmienna wolna w wyrażeniu które zliczymy w mapie  
   jest związana w "całym", takie wyrazenia chcemy uzwgledniac na kandydatow do uproszczenia przez cse. Wyrazenia wkladane do mapy sa przemianowane przez 
   rename_expr, wiec dwa rownowazne podwyrazenia w mapie zostana zliczone jako rowne. Jesli znajdziemy "powtarzajace" sie wyrazenie, 
   bedzeiemy je mogli uproscić przez cse*) 
  match e with
  | Int _ -> ExprMap.empty  
  | Bool _ -> ExprMap.empty   
  | Var x -> ExprMap.empty
  | If(c, t, f) ->  
      let rec_val = merge_hist (build_hist c m) (merge_hist (build_hist t m) (build_hist f m ) ) in 
      if (not_contain e m) then hist_inc (rename_expr e) rec_val else rec_val 
  | Binop(_, e1, e2) -> 
    let rec_val = (merge_hist (build_hist e1 m) (build_hist e2 m) ) in 
    if (not_contain e m ) then hist_inc (rename_expr e) rec_val else rec_val
  | Let(x, e1, e2) -> 
    let rec_val = merge_hist (build_hist e1 m) (build_hist e2 (M.add x 1 m) ) in 
    if (not_contain e m ) then hist_inc (rename_expr e) rec_val else rec_val


let find_key_gt_one (h : histogram) : expr option = (*zwraca z mapy klucz z wartością > 1, lub none jeśli taki nie istnieje*)
  let predicate _ v = v > 1 in
  let rec find_key_gt_one_rec map =
    match ExprMap.choose_opt map with
    | Some (key, value) ->
      if predicate key value then Some key
      else find_key_gt_one_rec (ExprMap.remove key map) 
    | None -> None
  in
  find_key_gt_one_rec h 
  

let rec subst (e : expr) (olde : expr) (new_val : expr) : expr = (*wykonuje podstawienie - zamieniamy poddrzewa e a-równoważne z pat na new_val*)
  if rename_expr e = olde then new_val 
  else  (*zakladamy ze pat ma nazwy zmiennych opdowiadajace przemianowaniu przez rename_expr *)
    match e with  
    | Var x -> e
    | Int v -> e 
    | Bool b -> e 
    | If(a, b, c) -> If(subst a olde new_val, subst b olde new_val, subst c olde new_val) 
    | Let(x, a, b) -> Let(x, subst a olde new_val, subst b olde new_val) 
    | Binop(op, a, b) -> Binop(op, subst a olde new_val, subst b olde new_val) 


let rec rcse (e : expr) : expr option = (*funckja rekurencyjna wykonująca cse*)
  let dmap = build_hist e M.empty in
  match find_key_gt_one dmap with
  | Some e1 -> Some (Let("$v", e1, (subst e e1 (Var "$v"))) ) (*znaleźliśmy równoważne podwyrażenia więc zastępujemy je nową zmienną i zwracamy *)
  | None -> (* jesli na poziome e nie wystepuja podwyrazenia rownowazne, próbujemy zaaplikować zrobić cse na podwyrażeniach e*)
    match e with
    | Var _ | Int _ | Bool _ -> None
    | Binop(op, e1, e2) ->
      (match rcse e1, rcse e2 with
      | Some e11, _ -> Some (Binop(op, e11, e2))
      | _, Some e22 -> Some (Binop(op, e1, e22))
      | _ -> None)
    | If (a, b, c) ->
      (match rcse a, rcse b, rcse c with
      | Some aa, _, _ -> Some (If(aa, b, c))
      | _, Some bb, _ -> Some (If(a, bb, c))
      | _, _, Some cc -> Some (If(a, b, cc))
      | _ -> None)
    | Let(x, e1, e2) ->
      (match rcse e1, rcse e2 with
      | Some e11, _ -> Some (Let(x, e11, e2))
      | _, Some e22 -> Some (Let(x, e1, e22))
      | _ -> None)

let cse (e : expr) : expr option = (*funkcja nierekurencyjna cse*)
  rcse e 

