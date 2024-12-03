%{
#include "ast.h"
#include "parser.h"
%}


digit           [0-9]
letter          [a-zA-Z]
identifier      {letter}({letter}|{digit})*
number          {digit}+

%%

"let"                   { return LET; }
"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"print"                 { return PRINT; }
"is"                    { return IS; }

"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
";"                     { return SEMICOLON; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MULTIPLY; }
"/"                     { return DIVIDE; }
">"                     { return GT; }
"<"                     { return LT; }
">="                    { return GE; }
"<="                    { return LE; }
"=="                    { return EQ; }
"!="                    { return NE; }

{number}                { yylval.num = atof(yytext); return NUMBER; }
{identifier}            { yylval.id = strdup(yytext); return IDENTIFIER; }

[ \t\r\n]+              { /* Não retorna nada */ }

.                       { 
    fprintf(stderr, "Erro: Caractere inesperado '%s'\n", yytext);
    exit(1);
}

%%

int yywrap() { 
    return 1; 
}
