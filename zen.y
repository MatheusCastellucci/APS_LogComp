%{
    /* C Declarations */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <llvm-c/Core.h>
    #include <llvm-c/ExecutionEngine.h>
    #include <llvm-c/Target.h>
    #include <llvm-c/Analysis.h>
    #include "symbol_table.h"
    #include "codegen.h"

    /* External declarations */
    extern int yylex();
    void yyerror(const char *s);

    /* Global LLVM variables */
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    LLVMValueRef current_function;

    /* Integer type */
    LLVMTypeRef int_type;

    /* Initialize LLVM */
    void init_llvm() {
        module = LLVMModuleCreateWithName("zen_module");
        builder = LLVMCreateBuilder();
        int_type = LLVMInt32Type();
    }

    /* Finalize LLVM */
    void finalize_llvm() {
        LLVMDumpModule(module);
        LLVMDisposeBuilder(builder);
        LLVMDisposeModule(module);
    }
%}

%union {
    int intVal;
    char* strVal;
    LLVMValueRef value;
    struct ParamList* paramList;
    struct ArgList* argList;
    struct ElseClause* else_clause;
    struct Statements* statements;
    struct Statement* statement;
}

/* Tokens */
%token <intVal> NUMBER
%token <strVal> STRING IDENTIFIER
%token LET IS IF ELSE WHILE FOR IN FUNCTION END RETURN PRINT INPUT
%token PLUS MINUS TIMES DIVIDED_BY
%token EQUALS NOT_EQUALS GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%token AND OR NOT
%token SEMICOLON COMMA LPAREN RPAREN

%token UMINUS

/* Operator Precedence and Associativity */
%nonassoc LOWEST
%left OR
%left AND
%left EQUALS NOT_EQUALS
%left GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%left PLUS MINUS
%left TIMES DIVIDED_BY
%right NOT UMINUS

/* Type Declarations for Non-Terminals */
%type <statements> program statements non_empty_statements
%type <statement> statement
%type <statement> variable_declaration assignment function_declaration
%type <statement> control_structure if_statement while_loop for_loop
%type <statement> expression_statement print_statement return_statement
%type <value> expression logical_or_expression logical_and_expression
%type <value> equality_expression relational_expression additive_expression
%type <value> multiplicative_expression unary_expression primary_expression
%type <paramList> parameter_list parameter_list_opt
%type <argList> argument_list argument_list_opt

/* We expect one shift/reduce conflict */
%expect 1

%%

program:
    statements
    {
        /* Initialize LLVM */
        init_llvm();

        /* Generate code */
        if ($1 != NULL) {
            codegen_statements($1);
        }

        /* Finalize LLVM */
        finalize_llvm();
    }
;


statements:
    non_empty_statements
    {
        $$ = $1;
    }
    | /* empty */
    {
        $$ = NULL;
    }
;

non_empty_statements:
    statement
    {
        struct Statements* new_node = malloc(sizeof(struct Statements));
        new_node->statement = $1;
        new_node->next = NULL;
        $$ = new_node;
    }
    | statement non_empty_statements
    {
        struct Statements* new_node = malloc(sizeof(struct Statements));
        new_node->statement = $1;
        new_node->next = $2;
        $$ = new_node;
    }
;

statement:
    variable_declaration
    {
        $$ = $1;
    }
    | assignment
    {
        $$ = $1;
    }
    | function_declaration
    {
        $$ = $1;
    }
    | control_structure
    {
        $$ = $1;
    }
    | expression_statement
    {
        $$ = $1;
    }
    | print_statement
    {
        $$ = $1;
    }
    | return_statement
    {
        $$ = $1;
    }
    | SEMICOLON /* Empty statement */
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_EMPTY_STATEMENT;
        $$ = stmt;
    }
;

variable_declaration:
    LET IDENTIFIER SEMICOLON
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_VARIABLE_DECLARATION;
        stmt->data.variable_declaration.identifier = strdup($2);
        stmt->data.variable_declaration.value = NULL;
        $$ = stmt;
    }
    | LET IDENTIFIER IS expression SEMICOLON
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_VARIABLE_DECLARATION;
        stmt->data.variable_declaration.identifier = strdup($2);
        stmt->data.variable_declaration.value = $4;
        $$ = stmt;
    }
;

assignment:
    IDENTIFIER IS expression SEMICOLON
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_ASSIGNMENT;
        stmt->data.assignment.identifier = strdup($1);
        stmt->data.assignment.expression = $3;
        $$ = stmt;
    }
;

function_declaration:
    FUNCTION IDENTIFIER LPAREN parameter_list_opt RPAREN statements END
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_FUNCTION_DECLARATION;
        stmt->data.function_declaration.identifier = strdup($2);
        stmt->data.function_declaration.params = $4;
        stmt->data.function_declaration.body = $6;
        $$ = stmt;
    }
;

parameter_list_opt:
    /* empty */
    {
        $$ = NULL;
    }
    | parameter_list
    {
        $$ = $1;
    }
;

parameter_list:
    IDENTIFIER
    {
        struct ParamList* params = malloc(sizeof(struct ParamList));
        params->param_count = 1;
        params->param_names = malloc(sizeof(char*));
        params->param_names[0] = strdup($1);
        $$ = params;
    }
    | IDENTIFIER COMMA parameter_list
    {
        $$ = $3;
        $$->param_count += 1;
        $$->param_names = realloc($$->param_names, sizeof(char*) * $$->param_count);
        $$->param_names[$$->param_count - 1] = strdup($1);
    }
;

control_structure:
    if_statement
    {
        $$ = $1;
    }
    | while_loop
    {
        $$ = $1;
    }
    | for_loop
    {
        $$ = $1;
    }
;

if_statement:
    IF expression statements END
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_IF_STATEMENT;
        stmt->data.if_statement.condition = $2;
        stmt->data.if_statement.then_branch = $3;
        stmt->data.if_statement.else_clause = NULL;
        $$ = stmt;
    }
    | IF expression statements ELSE statements END
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_IF_STATEMENT;
        stmt->data.if_statement.condition = $2;
        stmt->data.if_statement.then_branch = $3;
        struct ElseClause* else_clause = malloc(sizeof(struct ElseClause));
        else_clause->statements = $5;
        stmt->data.if_statement.else_clause = else_clause;
        $$ = stmt;
    }
;

while_loop:
    WHILE expression statements END
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_WHILE_LOOP;
        stmt->data.while_loop.condition = $2;
        stmt->data.while_loop.body = $3;
        $$ = stmt;
    }
;

for_loop:
    FOR IDENTIFIER IN expression statements END
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_FOR_LOOP;
        stmt->data.for_loop.iterator = strdup($2);
        stmt->data.for_loop.end_expression = $4;
        stmt->data.for_loop.body = $5;
        $$ = stmt;
    }
;

expression_statement:
    expression SEMICOLON
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_EXPRESSION_STATEMENT;
        stmt->data.expression_statement = $1;
        $$ = stmt;
    }
;

print_statement:
    PRINT expression SEMICOLON
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_PRINT_STATEMENT;
        stmt->data.print_statement.expression = $2;
        $$ = stmt;
    }
;

return_statement:
    RETURN expression SEMICOLON
    {
        struct Statement* stmt = malloc(sizeof(struct Statement));
        stmt->type = STMT_RETURN_STATEMENT;
        stmt->data.return_statement.expression = $2;
        $$ = stmt;
    }
;

expression:
    logical_or_expression
    {
        $$ = $1;
    }
;

logical_or_expression:
    logical_or_expression OR logical_and_expression
    {
        $$ = LLVMBuildOr(builder, $1, $3, "ortmp");
    }
    | logical_and_expression %prec LOWEST
    {
        $$ = $1;
    }
;

logical_and_expression:
    logical_and_expression AND equality_expression
    {
        $$ = LLVMBuildAnd(builder, $1, $3, "andtmp");
    }
    | equality_expression %prec LOWEST
    {
        $$ = $1;
    }
;

equality_expression:
    equality_expression EQUALS relational_expression
    {
        $$ = LLVMBuildICmp(builder, LLVMIntEQ, $1, $3, "eqtmp");
    }
    | equality_expression NOT_EQUALS relational_expression
    {
        $$ = LLVMBuildICmp(builder, LLVMIntNE, $1, $3, "netmp");
    }
    | relational_expression %prec LOWEST
    {
        $$ = $1;
    }
;

relational_expression:
    relational_expression GREATER_THAN additive_expression
    {
        $$ = LLVMBuildICmp(builder, LLVMIntSGT, $1, $3, "gttmp");
    }
    | relational_expression LESS_THAN additive_expression
    {
        $$ = LLVMBuildICmp(builder, LLVMIntSLT, $1, $3, "lttmp");
    }
    | relational_expression GREATER_OR_EQUAL additive_expression
    {
        $$ = LLVMBuildICmp(builder, LLVMIntSGE, $1, $3, "getmp");
    }
    | relational_expression LESS_OR_EQUAL additive_expression
    {
        $$ = LLVMBuildICmp(builder, LLVMIntSLE, $1, $3, "letmp");
    }
    | additive_expression %prec LOWEST
    {
        $$ = $1;
    }
;

additive_expression:
    additive_expression PLUS multiplicative_expression
    {
        $$ = LLVMBuildAdd(builder, $1, $3, "addtmp");
    }
    | additive_expression MINUS multiplicative_expression
    {
        $$ = LLVMBuildSub(builder, $1, $3, "subtmp");
    }
    | multiplicative_expression %prec LOWEST
    {
        $$ = $1;
    }
;

multiplicative_expression:
    multiplicative_expression TIMES unary_expression
    {
        $$ = LLVMBuildMul(builder, $1, $3, "multmp");
    }
    | multiplicative_expression DIVIDED_BY unary_expression
    {
        $$ = LLVMBuildSDiv(builder, $1, $3, "divtmp");
    }
    | unary_expression %prec LOWEST
    {
        $$ = $1;
    }
;

unary_expression:
    MINUS unary_expression %prec UMINUS
    {
        $$ = LLVMBuildNeg(builder, $2, "negtmp");
    }
    | NOT unary_expression
    {
        $$ = LLVMBuildNot(builder, $2, "nottmp");
    }
    | primary_expression
    {
        $$ = $1;
    }
;

primary_expression:
    IDENTIFIER LPAREN argument_list_opt RPAREN
    {
        LLVMValueRef func = LLVMGetNamedFunction(module, $1);
        if (!func) {
            fprintf(stderr, "Error: Undefined function '%s'\n", $1);
            exit(1);
        }

        LLVMTypeRef funcType = LLVMTypeOf(func);
        if (!funcType) {
            fprintf(stderr, "Error: Unable to determine type of function '%s'\n", $1);
            exit(1);
        }

        LLVMValueRef result = LLVMBuildCall2(
            builder,
            LLVMGetElementType(funcType),
            func,
            $3->args,
            $3->arg_count,
            "calltmp"
        );
        $$ = result;
    }
    | IDENTIFIER
    {
        LLVMValueRef var = get_variable($1);
        if (!var) {
            fprintf(stderr, "Error: Undefined variable '%s'\n", $1);
            exit(1);
        }

        LLVMTypeRef varType = LLVMGetElementType(LLVMTypeOf(var));
        $$ = LLVMBuildLoad2(builder, varType, var, $1);
    }
    | NUMBER
    {
        $$ = LLVMConstInt(int_type, $1, 0);
    }
    | LPAREN expression RPAREN
    {
        $$ = $2;
    }
;

argument_list_opt:
    /* empty */
    {
        $$ = malloc(sizeof(struct ArgList));
        $$->arg_count = 0;
        $$->args = NULL;
    }
    | argument_list
    {
        $$ = $1;
    }
;

argument_list:
    expression
    {
        $$ = malloc(sizeof(struct ArgList));
        $$->arg_count = 1;
        $$->args = malloc(sizeof(LLVMValueRef));
        $$->args[0] = $1;
    }
    | expression COMMA argument_list
    {
        $$ = $3;
        $$->arg_count += 1;
        $$->args = realloc($$->args, sizeof(LLVMValueRef) * $$->arg_count);
        $$->args[$$->arg_count - 1] = $1;
    }
;
%%

/* Error Handling */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* Main Function */
int main(int argc, char **argv) {
    return yyparse();
}
