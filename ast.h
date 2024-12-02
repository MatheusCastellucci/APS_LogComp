#ifndef AST_H
#define AST_H

#include <stdlib.h>

typedef struct ASTNode ASTNode;
typedef struct ASTNodeList ASTNodeList;

typedef enum {
    NODE_VAR_DECL,
    NODE_ASSIGNMENT,
    NODE_FUNCTION,
    NODE_FUNCTION_CALL,
    NODE_IF,
    NODE_WHILE,
    NODE_PRINT,
    NODE_RETURN,
    NODE_BINOP,
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_BLOCK
} NodeType;

struct ASTNode {
    NodeType type;
    char *identifier;       // For variable/function names
    int number;             // For numeric values
    char binop;             // For binary operators
    ASTNode *left;          // For left-hand expressions
    ASTNode *right;         // For right-hand expressions
    ASTNodeList *parameters; // For function parameters
    ASTNodeList *body;      // For blocks or function bodies
    ASTNode *condition;     // For if/while conditions
    ASTNode *then_block;    // For the "then" block in if statements
    ASTNode *else_block;    // For the "else" block in if statements
};

struct ASTNodeList {
    ASTNode *node;          // Current node in the list
    ASTNodeList *next;      // Pointer to the next node in the list
};

// Function prototypes for creating nodes
ASTNode *create_var_decl_node(char *identifier, ASTNode *expression);
ASTNode *create_assignment_node(char *identifier, ASTNode *expression);
ASTNode *create_function_node(char *identifier, ASTNodeList *parameters, ASTNodeList *body); // Fixed
ASTNode *create_function_call_node(char *identifier, ASTNodeList *arguments);
ASTNode *create_if_node(ASTNode *condition, ASTNode *then_block, ASTNode *else_block);
ASTNode *create_while_node(ASTNode *condition, ASTNodeList *body); // Fixed
ASTNode *create_print_node(ASTNode *expression);
ASTNode *create_return_node(ASTNode *expression);
ASTNode *create_binop_node(char op, ASTNode *left, ASTNode *right);
ASTNode *create_number_node(int value);
ASTNode *create_identifier_node(char *identifier);
ASTNode *create_block_node(ASTNodeList *statements);

ASTNodeList *create_statement_list(ASTNode *statement, ASTNodeList *next);
ASTNodeList *create_parameter_list(char *identifier, ASTNodeList *next);
ASTNodeList *create_argument_list(ASTNode *expression, ASTNodeList *next);

#endif // AST_H
