%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"

extern FILE *yyin; // Declaração para redirecionar a entrada do lexer

// Declaração de funções externas e variáveis globais
extern int yylex(); // Função do lexer
void yyerror(const char *s); // Função para reportar erros no parser

ASTNode *ast_root; // Raiz da AST (Árvore Sintática Abstrata)
%}

%defines "parser.h"

// Definição de tipos para o parser
%union {
    int num;               // Para valores numéricos
    char *id;              // Para identificadores
    ASTNode *node;         // Para nós da AST
    ASTNodeList *node_list; // Para listas de nós da AST
}

// Declaração dos tokens
%token <id> IDENTIFIER
%token <num> NUMBER
%token LET IF ELSE WHILE PRINT IS
%token LBRACE RBRACE SEMICOLON LPAREN RPAREN
%token PLUS MINUS MULTIPLY DIVIDE GT LT GE LE EQ NE

// Declaração dos tipos retornados pelas regras
%type <node> program statement expression term factor variable_declaration assignment if_statement while_loop print_statement block
%type <node_list> statements

%%

// Regra principal do programa
program:
    statements { 
        ast_root = create_block_node($1); // Cria a raiz da AST como um bloco com as declarações
    }
    ;

// Conjunto de declarações (statements)
statements:
    statement { 
        $$ = create_statement_list($1, NULL); // Lista com uma única declaração
    }
    | statement statements { 
        $$ = create_statement_list($1, $2); // Lista com múltiplas declarações
    }
    ;

// Declaração de uma única instrução
statement:
    variable_declaration
    | assignment
    | if_statement
    | while_loop
    | print_statement
;

// Declaração de variável
variable_declaration:
    LET IDENTIFIER SEMICOLON { 
        $$ = create_var_decl_node($2, NULL); // Declara variável sem inicialização
    }
    | LET IDENTIFIER IS expression SEMICOLON { 
        $$ = create_var_decl_node($2, $4); // Declara variável com inicialização
    }
    ;

// Atribuição de valor a uma variável
assignment:
    IDENTIFIER IS expression SEMICOLON { 
        $$ = create_assignment_node($1, $3); 
    }
    ;

// Estrutura condicional (if/else)
if_statement:
    IF expression block { 
        $$ = create_if_node($2, create_block_node($3->body), NULL); // Condicional sem bloco else
    }
    | IF expression block ELSE block { 
        $$ = create_if_node($2, create_block_node($3->body), create_block_node($5->body)); // Condicional com bloco else
    }
    ;

// Estrutura de repetição (while)
while_loop:
    WHILE expression block { 
        $$ = create_while_node($2, $3->body); // Laço while com corpo de instruções
    }
    ;

// Comando de impressão
print_statement:
    PRINT expression SEMICOLON { 
        $$ = create_print_node($2); // Imprime a expressão
    }
    ;

// Bloco de instruções
block:
    LBRACE statements RBRACE { 
        $$ = create_block_node((ASTNodeList *)$2); // Conjunto de instruções dentro de chaves
    }
    ;

// Expressões (operações aritméticas e relacionais)
expression:
    expression PLUS term { $$ = create_binop_node('+', $1, $3); } // Soma
    | expression MINUS term { $$ = create_binop_node('-', $1, $3); } // Subtração
    | term { $$ = $1; } // Termo isolado
    | expression GT term { $$ = create_binop_node('>', $1, $3); } // Maior que
    | expression LT term { $$ = create_binop_node('<', $1, $3); } // Menor que
    | expression GE term { $$ = create_binop_node('G', $1, $3); } // Maior ou igual
    | expression LE term { $$ = create_binop_node('L', $1, $3); } // Menor ou igual
    | expression EQ term { $$ = create_binop_node('=', $1, $3); } // Igualdade
    | expression NE term { $$ = create_binop_node('!', $1, $3); } // Diferente
    ;

// Termos (operações de multiplicação e divisão)
term:
    term MULTIPLY factor { 
        $$ = create_binop_node('*', $1, $3); // Multiplicação
    }
    | term DIVIDE factor { 
        $$ = create_binop_node('/', $1, $3); // Divisão
    }
    | factor { 
        $$ = $1; // Fator isolado
    }
    ;

// Fatores (números, identificadores, expressões entre parênteses)
factor:
    LPAREN expression RPAREN { 
        $$ = $2; // Expressão entre parênteses
    }
    | NUMBER { 
        $$ = create_number_node($1); // Número inteiro
    }
    | IDENTIFIER { 
        $$ = create_identifier_node($1); // Identificador
    }
    ;

%%

// Função principal do programa
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo.sns>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo fornecido
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    // Redireciona o arquivo para o lexer
    yyin = file;

    // Processa o arquivo com o parser
    if (yyparse() == 0) {
        codegen(ast_root);
    }

    fclose(file);
    return 0;
}

// Função para reportar erros de parsing
extern int yylineno;

void yyerror(const char *s) {
    fprintf(stderr, "Erro de parsing na linha %d: %s\n", yylineno, s);
    exit(1);
}
