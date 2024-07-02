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