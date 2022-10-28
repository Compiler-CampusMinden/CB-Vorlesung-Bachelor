grammar Hello;

start : stmt* ;

stmt  : ID '=' expr ';' | expr ';' ;

expr  : term ('+' term)* ;
term  : atom ('*' atom)* ;

atom  : ID | INT ;

ID    : [a-z][a-zA-Z]* ;
INT   : [0-9]+ ;
WS    : [ \t\n]+ -> skip ;
