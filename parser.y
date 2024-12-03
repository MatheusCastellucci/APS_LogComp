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
%token LET FUNCTION IF ELSE WHILE PRINT RETURN IS END
%token LBRACE RBRACE LPAREN RPAREN SEMICOLON COMMA
%token PLUS MINUS MULTIPLY DIVIDE GT LT GE LE EQ NE

%type <node> program statement expression term factor variable_declaration assignment function_declaration function_call if_statement while_loop print_statement return_statement block
%type <node_list> statements parameter_list argument_list

%%

program:
    statements { 
        printf("Debug: Parsed program\n");
        ast_root = create_block_node($1); 
    }
    ;

statements:
    statement { 
        printf("Debug: Parsed single statement\n");
        $$ = create_statement_list($1, NULL); 
    }
    | statement statements { 
        printf("Debug: Parsed multiple statements\n");
        $$ = create_statement_list($1, $2); 
    }
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
    LET IDENTIFIER SEMICOLON { 
        printf("Debug: Parsed variable declaration 'let %s;'\n", $2);
        $$ = create_var_decl_node($2, NULL); 
    }
    | LET IDENTIFIER IS expression SEMICOLON { 
        printf("Debug: Parsed variable declaration 'let %s is <expression>'\n", $2);
        $$ = create_var_decl_node($2, $4); 
    }
    ;

assignment:
    IDENTIFIER IS expression SEMICOLON { 
        printf("Debug: Parsed assignment '%s is <expression>'\n", $1);
        $$ = create_assignment_node($1, $3); 
    }
    ;

function_declaration:
    FUNCTION IDENTIFIER LPAREN parameter_list RPAREN block { 
        printf("Debug: Parsed function declaration with parameters\n");
        $$ = create_function_node($2, $4, (ASTNodeList *)$6); 
    }
    | FUNCTION IDENTIFIER LPAREN RPAREN block { 
        printf("Debug: Parsed function declaration without parameters\n");
        $$ = create_function_node($2, NULL, (ASTNodeList *)$5); 
    }
    ;

parameter_list:
    IDENTIFIER { 
        printf("Debug: Parsed parameter list with single parameter '%s'\n", $1);
        $$ = create_parameter_list($1, NULL); 
    }
    | IDENTIFIER COMMA parameter_list { 
        printf("Debug: Parsed parameter list with multiple parameters\n");
        $$ = create_parameter_list($1, $3); 
    }
    ;

function_call:
    IDENTIFIER LPAREN argument_list RPAREN SEMICOLON { 
        printf("Debug: Parsed function call with arguments\n");
        $$ = create_function_call_node($1, $3); 
    }
    | IDENTIFIER LPAREN RPAREN SEMICOLON { 
        printf("Debug: Parsed function call without arguments\n");
        $$ = create_function_call_node($1, NULL); 
    }
    ;

argument_list:
    expression { 
        printf("Debug: Parsed argument list with single expression\n");
        $$ = create_argument_list($1, NULL); 
    }
    | expression COMMA argument_list { 
        printf("Debug: Parsed argument list with multiple expressions\n");
        $$ = create_argument_list($1, $3); 
    }
    ;

if_statement:
    IF expression block END { 
        printf("Debug: Parsed if statement without else\n");
        $$ = create_if_node($2, $3, NULL); 
    }
    | IF expression block ELSE block END { 
        printf("Debug: Parsed if statement with else\n");
        $$ = create_if_node($2, $3, $5); 
    }
    ;

while_loop:
    WHILE expression block { 
        printf("Debug: Parsed while loop\n");
        $$ = create_while_node($2, (ASTNodeList *)$3); 
    }
    ;

print_statement:
    PRINT expression SEMICOLON { 
        printf("Debug: Parsed print statement\n");
        $$ = create_print_node($2); 
    }
    ;

return_statement:
    RETURN expression SEMICOLON { 
        printf("Debug: Parsed return statement\n");
        $$ = create_return_node($2); 
    }
    ;

block:
    LBRACE statements RBRACE { 
        printf("Debug: Parsed block\n");
        $$ = create_block_node((ASTNodeList *)$2); 
    }
    ;

expression:
    expression PLUS term { $$ = create_binop_node('+', $1, $3); }
    | expression MINUS term { $$ = create_binop_node('-', $1, $3); }
    | term { $$ = $1; }
    | expression GT term { $$ = create_binop_node('>', $1, $3); }
    | expression LT term { $$ = create_binop_node('<', $1, $3); }
    | expression GE term { $$ = create_binop_node('G', $1, $3); } // Use 'G' for >=
    | expression LE term { $$ = create_binop_node('L', $1, $3); } // Use 'L' for <=
    | expression EQ term { $$ = create_binop_node('=', $1, $3); }
    | expression NE term { $$ = create_binop_node('!', $1, $3); }
    ;

term:
    term MULTIPLY factor { 
        printf("Debug: Parsed multiplication term\n");
        $$ = create_binop_node('*', $1, $3); 
    }
    | term DIVIDE factor { 
        printf("Debug: Parsed division term\n");
        $$ = create_binop_node('/', $1, $3); 
    }
    | factor { 
        $$ = $1; 
    }
    ;

factor:
    LPAREN expression RPAREN { 
        printf("Debug: Parsed parenthesized expression\n");
        $$ = $2; 
    }
    | NUMBER { 
        printf("Debug: Parsed number: %d\n", $1);
        $$ = create_number_node($1); 
    }
    | IDENTIFIER { 
        printf("Debug: Parsed identifier: %s\n", $1);
        $$ = create_identifier_node($1); 
    }
    | function_call { 
        $$ = $1; 
    }
    ;

%%

int main() {
    if (yyparse() == 0) {
        codegen(ast_root);
    }
    return 0;
}

extern int yylineno;

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
    exit(1);
}
