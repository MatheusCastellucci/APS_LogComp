#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <llvm-c/Core.h>

/* Data Structures */

struct ParamList {
    int param_count;
    char** param_names;
};

struct ArgList {
    int arg_count;
    LLVMValueRef* args;
};

struct ElseClause {
    struct Statements* statements;
};

struct Statement;

struct Statements {
    struct Statement* statement;
    struct Statements* next;
};

enum StatementType {
    STMT_VARIABLE_DECLARATION,
    STMT_ASSIGNMENT,
    STMT_FUNCTION_DECLARATION,
    STMT_IF_STATEMENT,
    STMT_WHILE_LOOP,
    STMT_FOR_LOOP,
    STMT_EXPRESSION_STATEMENT,
    STMT_PRINT_STATEMENT,
    STMT_RETURN_STATEMENT,
    STMT_EMPTY_STATEMENT
};

struct Statement {
    enum StatementType type;
    union {
        struct {
            char* identifier;
            LLVMValueRef value;
        } variable_declaration;
        struct {
            char* identifier;
            LLVMValueRef expression;
        } assignment;
        struct {
            char* identifier;
            struct ParamList* params;
            struct Statements* body;
        } function_declaration;
        struct {
            LLVMValueRef condition;
            struct Statements* then_branch;
            struct ElseClause* else_clause;
        } if_statement;
        struct {
            LLVMValueRef condition;
            struct Statements* body;
        } while_loop;
        struct {
            char* iterator;
            LLVMValueRef end_expression;
            struct Statements* body;
        } for_loop;
        LLVMValueRef expression_statement;
        struct {
            LLVMValueRef expression;
        } print_statement;
        struct {
            LLVMValueRef expression;
        } return_statement;
    } data;
};

/* Function Declarations */
LLVMValueRef get_variable(const char* name);
void set_variable(const char* name, LLVMValueRef value);

#endif /* SYMBOL_TABLE_H */
