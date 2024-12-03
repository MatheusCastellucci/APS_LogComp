#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"

/**
 * Cria um nó de declaração de variável.
 * @param identifier Nome da variável.
 * @param expression Expressão de inicialização (opcional).
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_var_decl_node(char *identifier, ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para declaração de variável\n");
        exit(1);
    }
    node->type = NODE_VAR_DECL;
    node->identifier = strdup(identifier);
    node->right = expression;
    return node;
}

/**
 * Cria um nó de atribuição de variável.
 * @param identifier Nome da variável.
 * @param expression Expressão atribuída à variável.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_assignment_node(char *identifier, ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para atribuição\n");
        exit(1);
    }
    node->type = NODE_ASSIGNMENT;
    node->identifier = strdup(identifier);
    node->right = expression;
    return node;
}

/**
 * Cria um nó para a instrução "if".
 * @param condition Condição da instrução.
 * @param then_block Bloco executado se a condição for verdadeira.
 * @param else_block Bloco executado se a condição for falsa (opcional).
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_if_node(ASTNode *condition, ASTNode *then_block, ASTNode *else_block) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para instrução 'if'\n");
        exit(1);
    }
    node->type = NODE_IF;
    node->condition = condition;
    node->then_block = then_block;
    node->else_block = else_block;
    return node;
}

/**
 * Cria um nó para o loop "while".
 * @param condition Condição do loop.
 * @param body Corpo do loop.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_while_node(ASTNode *condition, ASTNodeList *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para loop 'while'\n");
        exit(1);
    }
    node->type = NODE_WHILE;
    node->condition = condition;
    node->body = body;
    return node;
}

/**
 * Cria um nó para a instrução "print".
 * @param expression Expressão a ser impressa.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_print_node(ASTNode *expression) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para instrução 'print'\n");
        exit(1);
    }
    node->type = NODE_PRINT;
    node->right = expression;
    return node;
}

/**
 * Cria um nó para uma operação binária.
 * @param op Operador binário (ex: '+', '-', '*', '/').
 * @param left Operando à esquerda.
 * @param right Operando à direita.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_binop_node(char op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para operação binária\n");
        exit(1);
    }
    node->type = NODE_BINOP;
    node->binop = op;
    node->left = left;
    node->right = right;
    return node;
}

/**
 * Cria um nó para um número literal.
 * @param value Valor do número.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_number_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para número literal\n");
        exit(1);
    }
    node->type = NODE_NUMBER;
    node->number = value;
    return node;
}

/**
 * Cria um nó para um identificador.
 * @param identifier Nome do identificador.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_identifier_node(char *identifier) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para identificador\n");
        exit(1);
    }
    node->type = NODE_IDENTIFIER;
    node->identifier = strdup(identifier);
    return node;
}

/**
 * Cria um nó para um bloco de código.
 * @param statements Lista de statements no bloco.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_block_node(ASTNodeList *statements) {
    if (!statements) {
        fprintf(stderr, "Erro: Bloco vazio\n");
        exit(1);
    }

    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para bloco\n");
        exit(1);
    }

    node->type = NODE_BLOCK;
    node->body = statements;

    // Validação: garante que todos os statements no bloco são válidos
    ASTNodeList *current = statements;
    while (current) {
        if (!current->node) {
            fprintf(stderr, "Erro: Statement nulo no bloco\n");
            exit(1);
        }
        current = current->next;
    }

    return node;
}

/**
 * Cria uma lista encadeada de statements.
 * @param statement Statement atual.
 * @param next Próximo statement na lista (opcional).
 * @return Ponteiro para a lista criada.
 */
ASTNodeList *create_statement_list(ASTNode *statement, ASTNodeList *next) {
    ASTNodeList *list = malloc(sizeof(ASTNodeList));
    if (!list) {
        fprintf(stderr, "Erro: Falha ao alocar memória para lista de statements\n");
        exit(1);
    }
    list->node = statement;
    list->next = next;
    return list;
}
