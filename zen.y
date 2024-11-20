%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    /* Definições para o yylval */
    typedef struct {
        int intVal;
        char* strVal;
    } YYSTYPE;

    #define YYSTYPE YYSTYPE

    void yyerror(const char *s);
    int yylex(void);

    /* Prototipando funções para liberar memória */
    void free_ast();
%}

%union {
    int intVal;
    char* strVal;
}

/* Declaração dos tokens */
%token LET IS IF ELSE WHILE FUNCTION END RETURN PRINT INPUT
%token PLUS MINUS TIMES DIVIDED_BY
%token EQUALS NOT_EQUALS GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%token AND OR NOT
%token NUMBER STRING IDENTIFIER
%token SEMICOLON COMMA LPAREN RPAREN

/* Precedência e associatividade (se necessário) */
%left OR
%left AND
%left EQUALS NOT_EQUALS GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%left PLUS MINUS
%left TIMES DIVIDED_BY
%right NOT

%%

program:
    /* Lista de declarações ou instruções */
    statements
;

statements:
    /* Pode ser vazio */
    | statement statements
;

statement:
    variable_declaration
    | assignment
    | function_declaration
    | control_structure
    | expression SEMICOLON
    | PRINT expression SEMICOLON
    | RETURN expression SEMICOLON
;

variable_declaration:
    LET IDENTIFIER SEMICOLON
    | LET IDENTIFIER IS expression SEMICOLON
;

assignment:
    IDENTIFIER IS expression SEMICOLON
;

function_declaration:
    FUNCTION IDENTIFIER LPAREN parameter_list_opt RPAREN statements END
;

parameter_list_opt:
    /* Pode não haver parâmetros */
    | parameter_list
;

parameter_list:
    IDENTIFIER
    | IDENTIFIER COMMA parameter_list
;

control_structure:
    if_statement
    | while_loop
;

if_statement:
    IF expression statements else_clause END
;

else_clause:
    /* O else é opcional */
    | ELSE statements
    | /* vazio */
;

while_loop:
    WHILE expression statements END
;

expression:
    expression PLUS expression
    | expression MINUS expression
    | expression TIMES expression
    | expression DIVIDED_BY expression
    | expression EQUALS expression
    | expression NOT_EQUALS expression
    | expression GREATER_THAN expression
    | expression LESS_THAN expression
    | expression GREATER_OR_EQUAL expression
    | expression LESS_OR_EQUAL expression
    | expression AND expression
    | expression OR expression
    | NOT expression
    | LPAREN expression RPAREN
    | NUMBER
    | STRING
    | IDENTIFIER
    | function_call
;

function_call:
    IDENTIFIER LPAREN argument_list_opt RPAREN
;

argument_list_opt:
    /* Pode não haver argumentos */
    | argument_list
;

argument_list:
    expression
    | expression COMMA argument_list
;

%%

/* Função de erro */
void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}

int main(int argc, char **argv) {
    if (yyparse() == 0) {
        printf("Análise sintática concluída com sucesso!\n");
    }
    return 0;
}

/* Função para liberar memória (se estiver usando AST) */
void free_ast() {
    /* Implementar se necessário */
}
