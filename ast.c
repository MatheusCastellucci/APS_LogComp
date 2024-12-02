#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *create_var_decl_node(char *identifier, ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECL;
    node->identifier = strdup(identifier);
    node->right = expression; // The assigned expression, if any
    return node;
}

ASTNode *create_assignment_node(char *identifier, ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGNMENT;
    node->identifier = strdup(identifier);
    node->right = expression;
    return node;
}

ASTNode *create_function_node(char *identifier, ASTNodeList *parameters, ASTNodeList *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION;
    node->identifier = strdup(identifier);
    node->parameters = parameters;
    node->body = body;
    return node;
}

ASTNode *create_function_call_node(char *identifier, ASTNodeList *arguments) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION_CALL;
    node->identifier = strdup(identifier);
    node->parameters = arguments;
    return node;
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *then_block, ASTNode *else_block) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->condition = condition;
    node->then_block = then_block;
    node->else_block = else_block;
    return node;
}

ASTNode *create_while_node(ASTNode *condition, ASTNodeList *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->condition = condition;
    node->body = body;
    return node;
}

ASTNode *create_print_node(ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->right = expression;
    return node;
}

ASTNode *create_return_node(ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->right = expression;
    return node;
}

ASTNode *create_binop_node(char op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->binop = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *create_number_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->number = value;
    return node;
}

ASTNode *create_identifier_node(char *identifier) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->identifier = strdup(identifier);
    return node;
}

ASTNode *create_block_node(ASTNodeList *statements) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_BLOCK;
    node->body = statements;
    return node;
}

ASTNodeList *create_statement_list(ASTNode *statement, ASTNodeList *next) {
    ASTNodeList *list = malloc(sizeof(ASTNodeList));
    list->node = statement;
    list->next = next;
    return list;
}

ASTNodeList *create_parameter_list(char *identifier, ASTNodeList *next) {
    ASTNode *param_node = create_identifier_node(identifier);
    ASTNodeList *list = malloc(sizeof(ASTNodeList));
    list->node = param_node;
    list->next = next;
    return list;
}

ASTNodeList *create_argument_list(ASTNode *expression, ASTNodeList *next) {
    ASTNodeList *list = malloc(sizeof(ASTNodeList));
    list->node = expression;
    list->next = next;
    return list;
}
