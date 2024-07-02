module type OrderedType = sig 
  type t 
  val compare : t -> t ->int 
end 


module type DICT = sig
  type key
  type 'a  dict
  val empty : 'a dict
  val insert :  key -> 'a -> 'a dict -> 'a dict
  val remove : key -> 'a dict -> 'a dict
  val find_opt : key -> 'a dict -> 'a option
  val find : key -> 'a dict -> 'a
  val to_list : 'a dict -> (key * 'a) list
end

module MakeListDict (Otyp:Map.OrderedType) : DICT with type key = Otyp.t = struct (* reprezentujemy to jako lista par (klucz, wartosc)*)
  type key = Otyp.t
  type 'a dict = ( key * 'a) list
  let empty = []
  let bool_of_int (k:int) = 
    match k with 
    | 0 -> false
    | k -> true 
  let remove k d = List.filter (fun (k', _) -> bool_of_int(Otyp.compare k k' ) ) d
  let insert k v d = (k, v) :: remove k d
  let find_opt k d = List.find_opt (fun (k', _) -> not (bool_of_int(Otyp.compare k k' )) ) d |> Option.map snd (* wartosc jest typu opt, gdyz moze nie istniec w dictie i 
     wtedy zwracamy None*)
  let find k d = List.find (fun (k', _) -> not (bool_of_int(Otyp.compare k k' )) ) d |> snd
  let to_list d = d
end

module CharListDict = MakeListDict(Char) 

let moj_dict = CharListDict.empty;;
(* tak dziala: *)
let moj_dict = CharListDict.insert 'a' 'a' moj_dict;; 
let moj_dict = CharListDict.insert 'b' 'b' moj_dict;;  
let moj_dict = CharListDict.insert 'c' 'c' moj_dict;;

let listowo  = CharListDict.to_list moj_dict;; 

let moj_dict = CharListDict.remove 'b' moj_dict;; 

let listowo = CharListDict.to_list moj_dict;;  

 




