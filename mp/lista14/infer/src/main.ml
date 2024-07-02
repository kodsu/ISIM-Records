open Lexer
open Parser
open TypeCheck
open Eval

let run s =
  let lexbuf = Lexing.from_string s in
  try
    let ast = Parser.prog Lexer.token lexbuf in
    Printf.printf "Parsed AST: %s\n" (Ast.string_of_expr ast);
    let tp = infer_type TypeCheck.env_empty ast in
    Printf.printf "Inferred type: %s\n" (Ast.string_of_tp tp);
    let value = eval_prog ast in
    Printf.printf "Evaluated value: %s\n" (Eval.string_of_value value)
  with
  | Lexer.SyntaxError msg ->
    Printf.eprintf "Syntax error: %s\n" msg
  | Parser.Error ->
    Printf.eprintf "Parse error at offset %d\n" (Lexing.lexeme_start lexbuf)
  | TypeCheck.Type_error ->
    Printf.eprintf "Type error\n"
  | Eval.Unbound_var x ->
    Printf.eprintf "Unbound variable: %s\n" x
  | Eval.Type_error ->
    Printf.eprintf "Type error\n"

let () =
  let inputs = [
    "fun x -> x";
    "fun x -> x x";
    "fun f y -> f 42 (f true y)";
  ] in
  List.iter run inputs
