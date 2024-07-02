type 'a symbol = 
  | T of string (*symbol nieterminalny*)
  | N of 'a (* symbol nieterminalny *)
type 'a grammar = ('a *('a symbol list) list ) list 

(*lista bo jest wiele par (klucz-wartość) 
   wartość to lista możliwych rezultatów do otrzymania z klucza
   który jest listą symboli*)

  (* ⟨E⟩ ::= ⟨E⟩ + ⟨E⟩ | ⟨E⟩ ∗ ⟨E⟩ | (⟨E⟩) | 1 | 2*)

let expr: unit grammar = 
  [(), [ [N (); T "+"; N ()];
         [N (); T "*"; N ()]; 
         [T "("; N (); T ")"];
         [T "1"]; 
         [T "2"]; ]] ;; 
(*todo: *)
(*
Random.int : int -> int — losowa liczba z zakresu 0..n-1
List.length : 'a list -> int — długosc listy
List.assoc : 'a -> ('a * 'b) list -> 'b — wyszukanie elementu na liście asocjacyjnej
String.concat : string -> string list -> string — konkatenacja listy stringów
z separatorem np: 
*)

(* to zeby zrozumiec typy *)
let cand2 (gr : 'a grammar) (nt: 'a) =  
  (List.assoc nt gr );;  

let chosen2 (gr : 'a grammar) (nt: 'a)= List.hd (cand2 gr nt) ;; 

let filter (sy: 'a symbol) = 
  match sy with 
  | T s -> s 
  | sy -> ""
 ;;  

(*wlasciwe: *)
let rec generate (gr : 'a grammar) (nt: 'a) = 
  let rec nth_list_el l n =
    match n with  
    | 0 -> List.hd l 
    | n -> nth_list_el (List.tl l) (n-1) 
  in    
  let random_el ls = 
    nth_list_el ls (Random.int  (List.length ls) ) 
  in
  let cand =  (List.assoc nt gr ) in 
  let chosen = random_el cand in (*cand jest  'a symbol list list, bo symbol może przejść na wiele rzeczy*) 
  String.concat "" (List.map (fun x -> match x with 
    | T s -> s 
    | N x -> generate gr x ) chosen ) ;; 

(*generate expr ();;*)

let pol : string grammar =
  [ "zdanie" , [[ N "grupa-podmiotu"; N "grupa-orzeczenia" ]]
  ; "grupa-podmiotu" , [[ N "przydawka"; N "podmiot" ]]
  ; "grupa-orzeczenia" , [[ N "orzeczenie"; N "dopelnienie" ]]
  ; "przydawka" , [[ T "Piekny " ];
  [T "Bogaty " ];
  [T "Wesoly " ]]
  ; "podmiot" , [[ T "policjant " ];
  [T "student " ];
  [T "piekarz " ]]
  ; "orzeczenie" , [[ T "zjadl " ];
  [T "pokochal " ];
  [T "zobaczyl " ]]
  ; "dopelnienie" , [[ T "zupe." ];
  [T "studentke." ];
  [T "sam siebie ." ];
  [T "instytut informatyki." ]]
  ] ;; 

generate pol "zdanie";; 

