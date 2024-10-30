grammar MiniC;


// Parser
program :  stmt* EOF ;


stmt    :  vardecl
        |  assign
        |  fndecl
        |  expr ';'
        |  block
        |  while
        |  cond
        |  return
        ;

vardecl :  type ID ('=' expr)? ';' ;
assign  :  ID '=' expr ';' ;

fndecl  :  type ID '(' params? ')' block ;
params  :  type ID (',' type ID)* ;
return  :  'return' expr ';' ;

fncall  :  ID '(' args? ')' ;
args    :  expr (',' expr)* ;

block   :  '{' stmt* '}' ;
while   :  'while' '(' expr ')' block ;
cond    :  'if' '(' expr ')' block ('else' block)? ;

expr    :  fncall
        |  expr '*' expr
        |  expr '/' expr
        |  expr '+' expr
        |  expr '-' expr
        |  expr '==' expr
        |  expr '!=' expr
        |  expr '>' expr
        |  expr '<' expr
        |  ID
        |  NUMBER
        |  STRING
        |  '(' expr ')'
        ;

type    :  'int' | 'string' | 'bool' ;


// Lexer
ID      :  [a-z][a-zA-Z0-9]* ;
NUMBER  :  [0-9]+ ;
STRING  :  '"' (~[\n\r"])* '"' ;

COMMENT :  '#' ~[\n\r]* -> skip ;
WS      :  [ \t\n\r]+ -> skip ;
