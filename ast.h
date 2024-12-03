#ifndef AST_H
#define AST_H

#include <stdlib.h>

/**
 * Enumeração dos tipos de nós na AST (Árvore de Sintaxe Abstrata).
 * Cada valor representa um tipo específico de construção sintática.
 */
typedef enum {
    NODE_VAR_DECL,       // Declaração de variável
    NODE_ASSIGNMENT,     // Atribuição de variável
    NODE_IF,             // Declaração de "if"
    NODE_WHILE,          // Declaração de "while"
    NODE_PRINT,          // Declaração de "print"
    NODE_BINOP,          // Operação binária (ex: +, -, *, /)
    NODE_NUMBER,         // Literal numérico
    NODE_IDENTIFIER,     // Identificador (variável ou nome)
    NODE_BLOCK           // Bloco de código (vários statements)
} NodeType;

/**
 * Estrutura que representa um nó na AST.
 */
typedef struct ASTNode {
    NodeType type;         // Tipo do nó
    char *identifier;      // Nome de identificadores (ex: variáveis)
    int number;            // Valor numérico (para literais)
    char binop;            // Operador binário (ex: '+', '-', etc.)
    struct ASTNode *left;  // Expressão à esquerda (para operações binárias)
    struct ASTNode *right; // Expressão à direita (para operações binárias)
    struct ASTNodeList *body; // Lista de nós (para blocos de código)
    struct ASTNode *condition; // Condição (para "if" e "while")
    struct ASTNode *then_block; // Bloco "então" (para "if")
    struct ASTNode *else_block; // Bloco "senão" (para "if")
} ASTNode;

/**
 * Estrutura que representa uma lista encadeada de nós da AST.
 */
typedef struct ASTNodeList {
    ASTNode *node;            // Nó atual na lista
    struct ASTNodeList *next; // Próximo nó na lista
} ASTNodeList;

// Prototipação das funções para criar diferentes tipos de nós na AST

/**
 * Cria um nó para declaração de variável.
 * @param identifier Nome da variável.
 * @param expression Expressão de inicialização (pode ser NULL).
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_var_decl_node(char *identifier, ASTNode *expression);

/**
 * Cria um nó para atribuição de variável.
 * @param identifier Nome da variável.
 * @param expression Expressão atribuída à variável.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_assignment_node(char *identifier, ASTNode *expression);

/**
 * Cria um nó para instruções "if".
 * @param condition Condição do "if".
 * @param then_block Bloco executado se a condição for verdadeira.
 * @param else_block Bloco executado se a condição for falsa (opcional).
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_if_node(ASTNode *condition, ASTNode *then_block, ASTNode *else_block);

/**
 * Cria um nó para loops "while".
 * @param condition Condição do loop.
 * @param body Corpo do loop.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_while_node(ASTNode *condition, ASTNodeList *body);

/**
 * Cria um nó para instruções "print".
 * @param expression Expressão a ser impressa.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_print_node(ASTNode *expression);

/**
 * Cria um nó para operações binárias.
 * @param op Operador binário (ex: '+', '-', '*', '/').
 * @param left Operando à esquerda.
 * @param right Operando à direita.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_binop_node(char op, ASTNode *left, ASTNode *right);

/**
 * Cria um nó para números literais.
 * @param value Valor numérico do literal.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_number_node(int value);

/**
 * Cria um nó para identificadores.
 * @param identifier Nome do identificador.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_identifier_node(char *identifier);

/**
 * Cria um nó para blocos de código.
 * @param statements Lista de statements no bloco.
 * @return Ponteiro para o nó criado.
 */
ASTNode *create_block_node(ASTNodeList *statements);

/**
 * Cria uma lista encadeada de statements.
 * @param statement Statement atual.
 * @param next Próximo statement na lista.
 * @return Ponteiro para a lista criada.
 */
ASTNodeList *create_statement_list(ASTNode *statement, ASTNodeList *next);

#endif // AST_H
