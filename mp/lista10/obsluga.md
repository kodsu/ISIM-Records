# Lita 10 MP - nauczmy sie uzywać naszego języka 
Mamy 3 języki: 
`imp-pure` - ewaluator czysto funkcyjny   
`imp-incr` - ewalutator z preinkrementacją  
`imp-ref`  - ewaluator metacykliczny (czyli że zmienne mają kind of adres?)  

przykładowy kod : 
```ml 
begin
	var x
	x := 42		
	begin

		var x
		x := 13
	end
	write x
end 
```  

tutuaj lepszy kodzik załączony od zioma wykładowego: 
```ml
var n
var p
var d
var k
begin
  read n
  p := 2
  while p <= n do
  begin
    d := 0
    k := 2
    while d = 0 and k*k <= p do
    begin
      if p / k * k = p then
        d := 1
      else skip
      k := k + 1
    end
    if d = 0 then
      write p
    else skip
    p := p + 1
  end
end
```
 
Analiza leksykalna: 
Mamy słowa kluczowe takie o właśnie: 
`begin end` -- "otwierają i zamykają nam jakieś sekcje"  
`if <bool expr> then <> else <>` 
`do`
`read write` -- wygląda jak I/O 
`var x` -- wprowadza "zmienną" x 
 `skip` -- nie wiem 
 `true false not and or` -- operatory logiczne 

Nazwy zmiennych mają składać się z liter|cyfr lub podłóg, ale nie mogą sie zaczynać od cyfr.  
Operatory(leksykalnie): 
` = <> <= >= < > * - / ( ) := (prypisanie)` 

Od chata 
stmt (instrukcje):

    Block of stmt list: blok instrukcji.    
    Assgn of var * aexp: przypisanie wartości wyrażenia arytmetycznego do zmiennej.  
    If of bexp * stmt * stmt: instrucja warunkowa.    
    While of bexp * stmt: pętla while.    
    Read of var: odczyt wartości do zmiennej.  
    Write of aexp: wypisanie wartości wyrażenia arytmetycznego.  

Składniowo stmt: 

```ml
stmt: (*tutaj parsujemy cały program*)
  | SKIP { Block [] } (*pusta instrukcja, może potrzebna w jakichś elsach*)
  | BEGIN s=list(stmt) END { Block s } (*nowy blok w środku*)
  | x=IDENT; ASSGN e=aexp { Assgn(x, e) } (*przypisanie wartości (do istniejacaj zmiennej) *)
  | IF; c=bexp; THEN; s1=stmt; ELSE; s2=stmt { If(c, s1, s2) } (*If nexp then <blok> then <blok> *) 
  | WHILE; c=bexp; DO; s=stmt { While(c, s) } (*while bexp DO <blok> *)
  | READ; x=IDENT { Read x } (*I/O*)
  | WRITE; e=aexp { Write e }
  ;
```

komenda do odpalania kodu, `<plik.imp>` ma być w folderze języka : 
``` 
dune exec imp <plik.imp> 
``` 

