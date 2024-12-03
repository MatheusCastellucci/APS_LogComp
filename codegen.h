#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <llvm-c/Core.h>

// ----------------------------------------------------------------------------
// Declaração de funções para geração de código (LLVM IR) a partir da AST
// ----------------------------------------------------------------------------

// Função principal para inicializar a geração de código e compilar a AST
// Entrada: nó raiz da AST
// Saída: gera o código LLVM IR correspondente
void codegen(ASTNode *node);

// ----------------------------------------------------------------------------
// Funções para geração de LLVM IR específicas para tipos de nós da AST
// ----------------------------------------------------------------------------

// Gera código LLVM para qualquer nó da AST
LLVMValueRef codegen_node(ASTNode *node);

// Gera código LLVM para declaração de variáveis
// Trata declarações como 'let x;' ou 'let x is <expressão>;'
LLVMValueRef codegen_var_decl(ASTNode *node);

// Gera código LLVM para atribuições
// Trata atribuições como 'x is <expressão>;'
LLVMValueRef codegen_assignment(ASTNode *node);

// Gera código LLVM para instruções de impressão
// Trata instruções como 'print <expressão>;'
LLVMValueRef codegen_print(ASTNode *node);

// Gera código LLVM para instruções condicionais (if/else)
// Trata estruturas como 'if <condição> { ... } else { ... }'
LLVMValueRef codegen_if(ASTNode *node);

// Gera código LLVM para loops while
// Trata estruturas como 'while <condição> { ... }'
LLVMValueRef codegen_while(ASTNode *node);

// Gera código LLVM para operações binárias
// Trata expressões como 'a + b', 'a - b', etc.
LLVMValueRef codegen_binop(ASTNode *node);

// Gera código LLVM para valores numéricos
// Trata números literais como '42' ou '3.14'
LLVMValueRef codegen_number(ASTNode *node);

// Gera código LLVM para identificadores
// Trata variáveis como 'x' ou 'y'
LLVMValueRef codegen_identifier(ASTNode *node);

// Gera código LLVM para blocos de código
// Trata blocos delimitados por '{ ... }'
void codegen_block(ASTNodeList *node_list);

#endif // CODEGEN_H
