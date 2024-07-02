type matrix = int*int*int*int;; 
let m_st ((a,_,_,_) : matrix) = a;; 
let m_nd ((_,a,_,_) : matrix) = a;; 
let m_rd ((_,_,a,_) : matrix) = a;; 
let m_4th ((_,_,_,a) : matrix) = a;; 
let create_matrix a b c d = ((a, b, c, d):matrix);; 

let matrix_mult (m:matrix) (n:matrix) = 
  let (a, b, c, d) = m in 
  let (aa, bb, cc, dd) = n in 
create_matrix (a*aa + b*cc) (a*bb + b*dd) (c*aa + d*cc) (c*bb + d*dd);;


let matrix_id = create_matrix 1 0 0 1;; 

let rec matrix_expt (m : matrix) k = 
    match k with 
    | 0 -> matrix_id 
    | k -> matrix_mult (matrix_expt m (k-1)) m  


let fib_base = create_matrix 1 1 1 0;; 

let fib_matrix k = 
    m_nd (matrix_expt fib_base k);;
(*tutaj koncza sie wlasciwe funkcje i zaczyna uzytkowanie i testing*)

let matrix_a = create_matrix 2 1 3 7;; 
let m_res = matrix_expt matrix_a 3 ;;  

print_int (m_st m_res);; print_newline();; 
print_int (m_nd m_res);; print_newline();; 
print_int (m_rd m_res);; print_newline();; 
print_int (m_4th m_res);; print_newline();;  
print_newline();; 
print_int (fib_matrix 4);; print_newline();; 
print_int (fib_matrix 20);; print_newline();; 




