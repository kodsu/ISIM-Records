module LeftistHeap = struct
  type ('a , 'b) heap =
  | HLeaf
  | HNode of int * ('a , 'b) heap * 'a * 'b * ('a , 'b) heap
  let rank = function HLeaf -> 0 | HNode (n , _ , _ , _ , _) -> n
  let least_prio = function HLeaf -> failwith "smutny czlowiek" | HNode (_, _, p, _, _) -> p
  let heap_ordered p = function
    | HLeaf -> true
    | HNode (_ , _ , p', _ , _) -> p <= p'
  let rec is_valid = function
    | HLeaf -> true
    | HNode (n , l , p , v , r) ->
      rank r <= rank l
      && rank r + 1 = n
      && heap_ordered p l
      && heap_ordered p r
      && is_valid l
      && is_valid r
  let make_node p v l r = 
    let rec depth node = 
        match node with 
      | HLeaf -> 0 
      | HNode(r, ls, pri, value, rs) -> 1 + depth rs 
    in   let ldep = depth l in let rdep = depth r in 
    if ldep >= rdep (*ls, rs*)
      then HNode(rdep+1, l, p, v, r) 
    else
      HNode(ldep+1, r, p, v, l)
  let rec heap_merge ah bh = 
    if ah = HLeaf then bh 
    else if bh = HLeaf then ah else 
    (*wlasciwa czesc*)
    let amin = least_prio ah in let bmin = least_prio bh in
    let hl, p, e, hr, h = if amin < bmin then 
      let HNode(_, ahl, ap, ae, ahr) = ah in ahl, ap, ae, ahr, bh
    else
      let HNode(_, bhl, bp, be, bhr) = bh in bhl, bp, be, bhr, ah 
    in 
      make_node p e hl (heap_merge hr h)
end

module type PRIO_QUEUE = sig
  type ('a, 'b) pq
  val empty : ('a, 'b) pq
  val insert : 'a -> 'b -> ('a, 'b) pq -> ('a, 'b) pq
  val pop : ('a, 'b) pq -> ('a, 'b) pq
  val min_with_prio : ('a, 'b) pq -> 'a * 'b
end

module HeapPrioQueue : PRIO_QUEUE = struct(*trzymamy to jako wcześniej zaimplementowane *)
  open LeftistHeap
  type ('a, 'b) pq = ('a, 'b) heap
  let empty = HLeaf
  let rec insert a x q = (*a klucz, b wartość, q kolejka*) 
    let git_heap = make_node a x HLeaf HLeaf 
    in
    heap_merge git_heap q 
  let pop q =
    match q with 
    | HLeaf -> failwith "smutny czlowiek 2"
    | HNode(n, l, p, v, r) -> heap_merge l r 
  let min_with_prio q = 
    match q with 
    | HLeaf -> failwith "smutny czlowiek 3"
    | HNode(n, l, p, v, r) -> p,v
end

module ListPrioQueue : PRIO_QUEUE = struct(*trzymamy to jako posortowana liste par*)
  type ('a, 'b) pq = ('a * 'b) list
  let empty = []
  let rec insert a x q = match q with
  | [] -> [a, x]
  | (b, y) :: ys -> if a < b then (a, x) :: q else (b, y) :: insert a x ys
  let pop q = List.tl q
  let min_with_prio q = List.hd q
end

module Pqsort = functor (PQ : PRIO_QUEUE) -> struct 
  let sec x = 
    match x with 
    | _, b -> b 
    | x -> failwith "smutny czlowiek 4"
  let sort xs = 
    let rec make_pq ys = 
      match ys with 
      | [] -> PQ.empty 
      | el::ys_ -> PQ.insert el el (make_pq ys_) 
  in let rec make_list pq = 
    if pq = PQ.empty then []  
    else (sec (PQ.min_with_prio pq) ) :: make_list (PQ.pop pq) 
  in let loc_pq = make_pq xs 
  in make_list loc_pq 
end 

module HeapPqSort = Pqsort(HeapPrioQueue);; 

let ziom = HeapPqSort.sort [12; 243; 123; 2; 9; 94; 423; 14; 23453254; 4222; 234];;



