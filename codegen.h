#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <llvm-c/Core.h>

// Function to initialize code generation and compile the AST
void codegen(ASTNode *node);

// Functions to generate LLVM IR for specific AST node types
LLVMValueRef codegen_node(ASTNode *node);
LLVMValueRef codegen_var_decl(ASTNode *node);
LLVMValueRef codegen_assignment(ASTNode *node);
LLVMValueRef codegen_print(ASTNode *node);
LLVMValueRef codegen_if(ASTNode *node);
LLVMValueRef codegen_while(ASTNode *node);
LLVMValueRef codegen_binop(ASTNode *node);
LLVMValueRef codegen_number(ASTNode *node);
LLVMValueRef codegen_identifier(ASTNode *node);
void codegen_block(ASTNodeList *node_list);

#endif // CODEGEN_H
