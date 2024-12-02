%{
#include "ast.h"
#include "parser.h"
%}

digit           [0-9]
letter          [a-zA-Z]
identifier      {letter}({letter}|{digit})*
number          {digit}+(\.{digit}+)?

%%

"let"                   { return LET; }
"function"              { return FUNCTION; }
"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"print"                 { return PRINT; }
"return"                { return RETURN; }
"is"                    { return IS; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
";"                     { return SEMICOLON; }
","                     { return COMMA; }
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

[ \t\r\n]+              { /* Ignore whitespace */ }

.                       { printf("Unexpected character: %s\n", yytext); exit(1); }

%%

int yywrap() { return 1; }
