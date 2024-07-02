%token <int> INT
%token <string> IDENT
%token TIMES DIV PLUS MINUS
%token EQ NEQ LT GT LEQ GEQ
%token AND OR NOT
%token ASSGN LPAREN RPAREN
%token BEGIN END IF THEN ELSE WHILE DO READ WRITE VAR SKIP TRUE FALSE
%token EOF

%start <Ast.prog> prog

%{
open Ast
%}

%right OR
%right AND
%right NOT
%left PLUS MINUS
%left TIMES DIV

%%

aexp: (*parsuje wyrażenia arytmetyczne *)
  | n=INT   { Int n }
  | x=IDENT { Var x }
  | LPAREN; e=aexp; RPAREN { e }
  | e1=aexp; PLUS;  e2=aexp { Binop(Add, e1, e2) }
  | e1=aexp; MINUS; e2=aexp { Binop(Sub, e1, e2) }
  | e1=aexp; TIMES; e2=aexp { Binop(Mul, e1, e2) }
  | e1=aexp; DIV;   e2=aexp { Binop(Div, e1, e2) }
  ;

cmpop: (*symbloe i rzyeczy do porównania*)
  | EQ  { Eq  }
  | NEQ { Neq }
  | LT  { Lt  }
  | GT  { Gt  }
  | LEQ { Leq }
  | GEQ { Geq }
  ;

bexp: (*wyrażenia o wartości typu bool*)
  | TRUE  { Bool true  }
  | FALSE { Bool false }
  | LPAREN; e=bexp; RPAREN { e }
  | e1=aexp; op=cmpop; e2=aexp { Cmp(op, e1, e2) }
  | e1=bexp; AND; e2=bexp { And(e1, e2) }
  | e1=bexp; OR;  e2=bexp { Or(e1, e2)  }
  | NOT; e=bexp { Not e }
  ;

stmt: (*tutaj parsujemy cały program*)
  | SKIP { Block [] } (*pusta instrukcja*)
  | BEGIN s=list(stmt) END { Block s } (*nowy blok w środku*)
  | x=IDENT; ASSGN e=aexp { Assgn(x, e) } (*przypisanie wartości (do istniejacaj zmiennej) *)
  | IF; c=bexp; THEN; s1=stmt; ELSE; s2=stmt { If(c, s1, s2) } (*If nexp then <blok> then <blok> *) 
  | WHILE; c=bexp; DO; s=stmt { While(c, s) } (*while bexp DO <blok> *)
  | READ; x=IDENT { Read x } (*I/O*)
  | WRITE; e=aexp { Write e }
  ;

var_decl:
  | VAR; x=IDENT { x }
  ;

prog:
  | vs=list(var_decl); s=stmt; EOF { (vs, s) }
  ;
