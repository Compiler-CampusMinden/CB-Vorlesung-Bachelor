grammar MiniLisp;


// Parser
program :  expr+ EOF ;


expr    :  literal
        |  symbol
        |  '(' expr* ')'
        ;

literal :  NUMBER
        |  STRING
        |  TRUE
        |  FALSE
        ;

symbol  : ID
        | OP
        ;


// Lexer
TRUE    :  'true' ;
FALSE   :  'false' ;
ID      :  [a-z][a-zA-Z0-9]* ;
NUMBER  :  [0-9]+ ;
OP      :  '+' | '-' | '*' | '/' | '=' | '>' | '<' ;
STRING  :  '"' (~[\n\r"])* '"' ;
COMMENT :  ';;' ~[\n\r]* -> skip ;
WS      :  [ ,\t\n\r]+ -> skip ;
