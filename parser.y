%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"

extern int yylex();
void yyerror(const char *s);

ASTNode *ast_root;
%}

%defines "parser.h"

%union {
    int num;               // For numeric values
    char *id;              // For identifiers
    ASTNode *node;         // For AST nodes
    ASTNodeList *node_list; // For lists of AST nodes
}

%token <id> IDENTIFIER
%token <num> NUMBER
%token LET FUNCTION IF ELSE WHILE PRINT RETURN IS
%token LBRACE RBRACE LPAREN RPAREN SEMICOLON COMMA
%token PLUS MINUS MULTIPLY DIVIDE GT LT GE LE EQ NE

%type <node> program statement expression term factor variable_declaration assignment function_declaration function_call if_statement while_loop print_statement return_statement block
%type <node_list> statements parameter_list argument_list

%%

program:
    statements { ast_root = create_block_node($1); }
    ;

statements:
    statement { $$ = create_statement_list($1, NULL); }
    | statement statements { $$ = create_statement_list($1, $2); }
    ;

statement:
    variable_declaration
    | assignment
    | function_declaration
    | function_call
    | if_statement
    | while_loop
    | print_statement
    | return_statement
    ;

variable_declaration:
    LET IDENTIFIER SEMICOLON { $$ = create_var_decl_node($2, NULL); }
    | LET IDENTIFIER IS expression SEMICOLON { $$ = create_var_decl_node($2, $4); }
    ;

assignment:
    IDENTIFIER IS expression SEMICOLON { $$ = create_assignment_node($1, $3); }
    ;

function_declaration:
    FUNCTION IDENTIFIER LPAREN parameter_list RPAREN block { $$ = create_function_node($2, $4, (ASTNodeList *)$6); }
    | FUNCTION IDENTIFIER LPAREN RPAREN block { $$ = create_function_node($2, NULL, (ASTNodeList *)$5); }
    ;

parameter_list:
    IDENTIFIER { $$ = create_parameter_list($1, NULL); }
    | IDENTIFIER COMMA parameter_list { $$ = create_parameter_list($1, $3); }
    ;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN SEMICOLON { $$ = create_function_call_node($1, $3); }
    | IDENTIFIER LPAREN RPAREN SEMICOLON { $$ = create_function_call_node($1, NULL); }
    ;

argument_list:
    expression { $$ = create_argument_list($1, NULL); }
    | expression COMMA argument_list { $$ = create_argument_list($1, $3); }
    ;

if_statement:
    IF expression block { $$ = create_if_node($2, $3, NULL); }
    | IF expression block ELSE block { $$ = create_if_node($2, $3, $5); }
    ;

while_loop:
    WHILE expression block { $$ = create_while_node($2, (ASTNodeList *)$3); }
    ;

print_statement:
    PRINT expression SEMICOLON { $$ = create_print_node($2); }
    ;

return_statement:
    RETURN expression SEMICOLON { $$ = create_return_node($2); }
    ;

block:
    LBRACE statements RBRACE { $$ = create_block_node((ASTNodeList *)$2); } // Wrap the statement list in a block node
    ;

expression:
    expression PLUS term { $$ = create_binop_node('+', $1, $3); }
    | expression MINUS term { $$ = create_binop_node('-', $1, $3); }
    | term { $$ = $1; }
    ;

term:
    term MULTIPLY factor { $$ = create_binop_node('*', $1, $3); }
    | term DIVIDE factor { $$ = create_binop_node('/', $1, $3); }
    | factor { $$ = $1; }
    ;

factor:
    LPAREN expression RPAREN { $$ = $2; }
    | NUMBER { $$ = create_number_node($1); }
    | IDENTIFIER { $$ = create_identifier_node($1); }
    | function_call { $$ = $1; }
    ;

%%

int main() {
    if (yyparse() == 0) {
        codegen(ast_root);
    }
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
