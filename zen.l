%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <llvm-c/Core.h>
    #include <llvm-c/ExecutionEngine.h>
    #include <llvm-c/Target.h>
    #include <llvm-c/Analysis.h>
    #include "zen.tab.h"
    #include "symbol_table.h"
%}

%%

[ \t\n]+             { /* Ignore whitespace */ }
"//".*               { /* Ignore single-line comments */ }
"/*"[^*]*"*"*[^*/]*"*/"  { /* Ignore multi-line comments */ }

"let"                { return LET; }
"is"                 { return IS; }
"if"                 { return IF; }
"else"               { return ELSE; }
"while"              { return WHILE; }
"for"                { return FOR; }
"in"                 { return IN; }
"function"           { return FUNCTION; }
"end"                { return END; }
"return"             { return RETURN; }
"print"              { return PRINT; }
"input"              { return INPUT; }
"and"                { return AND; }
"or"                 { return OR; }
"not"                { return NOT; }

"+"                  { return PLUS; }
"-"                  { return MINUS; }
"*"                  { return TIMES; }
"/"                  { return DIVIDED_BY; }
"=="                 { return EQUALS; }
"!="                 { return NOT_EQUALS; }
">"                  { return GREATER_THAN; }
"<"                  { return LESS_THAN; }
">="                 { return GREATER_OR_EQUAL; }
"<="                 { return LESS_OR_EQUAL; }
";"                  { return SEMICOLON; }
","                  { return COMMA; }
"("                  { return LPAREN; }
")"                  { return RPAREN; }

[0-9]+               {
                        yylval.intVal = atoi(yytext);
                        return NUMBER;
                    }

[a-zA-Z_][a-zA-Z0-9_]* {
                        yylval.strVal = strdup(yytext);
                        return IDENTIFIER;
                    }

.                    { fprintf(stderr, "Unknown character: %s\n", yytext); exit(1); }

%%

int yywrap() {
    return 1;
}
