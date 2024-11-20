%{
    #include "zen.tab.h"
%}

%%

/* Palavras-chave */
"let"                   return LET;
"is"                    return IS;
"if"                    return IF;
"else"                  return ELSE;
"while"                 return WHILE;
"function"              return FUNCTION;
"end"                   return END;
"return"                return RETURN;
"print"                 return PRINT;
"input"                 return INPUT;

/* Operadores matemáticos */
"plus"                  return PLUS;
"minus"                 return MINUS;
"times"                 return TIMES;
"divided by"            return DIVIDED_BY;

/* Operadores de comparação */
"equals"                return EQUALS;
"not equals"            return NOT_EQUALS;
"greater than"          return GREATER_THAN;
"less than"             return LESS_THAN;
"greater or equal"      return GREATER_OR_EQUAL;
"less or equal"         return LESS_OR_EQUAL;

/* Operadores lógicos */
"and"                   return AND;
"or"                    return OR;
"not"                   return NOT;

/* Literais */
[0-9]+                  { yylval.intVal = atoi(yytext); return NUMBER; }
\"([^\\\"]|\\.)*\"      { yylval.strVal = strdup(yytext); return STRING; }

/* Identificadores */
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.strVal = strdup(yytext); return IDENTIFIER; }

/* Símbolos e pontuação */
";"                     return SEMICOLON;
","                     return COMMA;
"("                     return LPAREN;
")"                     return RPAREN;

/* Espaços em branco (ignorar) */
[ \t\r\n]+              /* ignore whitespace */

/* Comentários (opcional) */
"#".*                   /* ignore comments */

%%

int yywrap(void) {
    return 1;
}
