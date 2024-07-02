%{
open Ast
%}

%token <int> INT
%token <string> IDENT
%token TIMES
%token DIV
%token PLUS
%token MINUS
%token LPAREN
%token RPAREN
%token AND
%token OR
%token EQ
%token LT
%token GT
%token LEQ
%token GEQ
%token NEQ
%token TRUE
%token FALSE
%token IF
%token THEN
%token ELSE
%token LET 
%token REC
%token IN
%token ARR
%token FUN
%token EOF
%token EXC 
%token SEM 
%token REF 
%token ASSIGN
%start <Ast.expr> prog

%nonassoc AND OR
%nonassoc EQ NEQ LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIV

%%

prog:
  | e = mixfix; EOF { e }
  ;

mixfix:
  | IF; e1 = mixfix; THEN; e2 = mixfix; ELSE; e3 = mixfix { If(e1, e2, e3) }
  | LET; x = IDENT; EQ; e1 = mixfix; IN; e2 = mixfix { Let(x, e1, e2) } 
  | LET; REC; f = IDENT; mid = arg_listeq; IN fin_body = mixfix { Let(f, App(Var "fix", Fun(f, mid)), fin_body) } 
  | FUN; x = IDENT; ARR e = mixfix { Fun(x, e) } 
  | FUN; x = IDENT; r = arg_list { Fun(x,r) }
  | e = expr { e }
  ;
(*interp "let f = fix (fun f -> fun x -> if x = 0 then 0 else 1+ f (x/2)  )  in f 20000000000000000"
 interp "let rec f x = if x = 0 then 0 else 1+ f (x - 1) in f 10";; dziala
interp"let rec f x = if x = 0 then 0 else 1+ f (x-1) in f 10";; nie dziala
interp "let rec f x =( if x < 2  then x else  f (x - 1) + f (x - 2) )  in f 25";; dziala -- fibonacii 
interp "let rec sum a b = if a = 0 then b else a * a + sum (a - 1) b  in sum 20 1 ";; dziala na dwoch zmiennych cos tam 
interp "let rec nwd a b = if b = 0 then a + 0 else nwd b ( mod a b)  in nwd 18 24 ";;

*)
arg_list: 
  | x = IDENT; w = arg_list {Fun(x,w)}
  | y = IDENT; ARR; l = expr {Fun(y,l)}
  ; 
arg_listeq: 
  | x = IDENT; w = arg_listeq {Fun(x,w)}
  | y = IDENT; EQ; l = mixfix {Fun(y,l)}
  ; 

expr:
  | REF; e1 = expr; {Ref(e1)}
  | EXC; e1 = expr {Deref(e1)} 
  | e1 = expr; ASSIGN; e2 = expr; SEM; e3 = expr {Assign(e1,e2,e3)} 
  | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
  | e1 = expr; MINUS; e2 = expr { Binop(Sub, e1, e2) }
  | e1 = expr; DIV; e2 = expr { Binop(Div, e1, e2) }
  | e1 = expr; TIMES; e2 = expr { Binop(Mult, e1, e2) }
  | e1 = expr; EQ; e2 = expr { Binop(Eq, e1, e2) }
  | e1 = expr; LT; e2 = expr { Binop(Lt, e1, e2) }
  | e1 = expr; GT; e2 = expr { Binop(Gt, e1, e2) }
  | e1 = expr; LEQ; e2 = expr { Binop(Leq, e1, e2) }
  | e1 = expr; GEQ; e2 = expr { Binop(Geq, e1, e2) }
  | e1 = expr; NEQ; e2 = expr { Binop(Neq, e1, e2) }
  | e1 = expr; AND; e2 = expr { Binop(And, e1, e2) }
  | e1 = expr; OR; e2 = expr { Binop(Or, e1, e2) }
  | e = app { e }
  ;

app:
  | e1 = app; e2 = base { App(e1, e2) }
  | e = base { e }
  ;

base:
  | i = INT { Int i }
  | x = IDENT { Var x }
  | LPAREN; e = mixfix; RPAREN { e }
  | TRUE { Bool true }
  | FALSE { Bool false }
  ;
