%{
#include "ast.h"
#include "parser.h"
%}

digit           [0-9]
letter          [a-zA-Z]
identifier      {letter}({letter}|{digit})*
number          {digit}+(\.{digit}+)? 

%%

"let"                   { printf("Token: LET\n"); return LET; }
"function"              { printf("Token: FUNCTION\n"); return FUNCTION; }
"if"                    { printf("Token: IF\n"); return IF; }
"else"                  { printf("Token: ELSE\n"); return ELSE; }
"end"                   { printf("Token: END\n"); return END; }
"while"                 { printf("Token: WHILE\n"); return WHILE; }
"print"                 { printf("Token: PRINT\n"); return PRINT; }
"return"                { printf("Token: RETURN\n"); return RETURN; }
"is"                    { printf("Token: IS\n"); return IS; }
"{"                     { printf("Token: LBRACE\n"); return LBRACE; }
"}"                     { printf("Token: RBRACE\n"); return RBRACE; }
"("                     { printf("Token: LPAREN\n"); return LPAREN; }
")"                     { printf("Token: RPAREN\n"); return RPAREN; }
";"                     { printf("Token: SEMICOLON\n"); return SEMICOLON; }
","                     { printf("Token: COMMA\n"); return COMMA; }
"+"                     { printf("Token: PLUS\n"); return PLUS; }
"-"                     { printf("Token: MINUS\n"); return MINUS; }
"*"                     { printf("Token: MULTIPLY\n"); return MULTIPLY; }
"/"                     { printf("Token: DIVIDE\n"); return DIVIDE; }
">"                     { printf("Token: GT\n"); return GT; }
"<"                     { printf("Token: LT\n"); return LT; }
">="                    { printf("Token: GE\n"); return GE; }
"<="                    { printf("Token: LE\n"); return LE; }
"=="                    { printf("Token: EQ\n"); return EQ; }
"!="                    { printf("Token: NE\n"); return NE; }

{number}                { printf("Token: NUMBER (%s)\n", yytext); yylval.num = atof(yytext); return NUMBER; }
{identifier}            { printf("Token: IDENTIFIER (%s)\n", yytext); yylval.id = strdup(yytext); return IDENTIFIER; }

[ \t\r\n]+              { /* Ignore whitespace */ }

.                       { printf("Unexpected character: %s\n", yytext); exit(1); }

%%

int yywrap() { return 1; }
