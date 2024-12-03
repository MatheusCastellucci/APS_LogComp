#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>

// Módulos LLVM globais
LLVMModuleRef module;
LLVMBuilderRef builder;
LLVMExecutionEngineRef engine;
LLVMValueRef current_function = NULL; // Referência para a função atual
LLVMValueRef named_values[100];       // Variáveis nomeadas armazenadas
int variable_index = 0;               // Índice para variáveis nomeadas

// Declaração de funções auxiliares
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

/**
 * Função principal para inicializar a geração de código LLVM e compilar a AST.
 * @param node Raiz da AST (Abstract Syntax Tree).
 */
void codegen(ASTNode *node) {
    // Inicializa o LLVM para execução nativa
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMLinkInMCJIT();
    char *error = NULL;

    // Cria o módulo LLVM
    module = LLVMModuleCreateWithName("module_sensei");
    builder = LLVMCreateBuilder();

    // Configura o engine de execução
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error) != 0) {
        fprintf(stderr, "Erro ao criar engine de execução: %s\n", error);
        exit(1);
    }

    // Garante que a função 'main' exista
    current_function = LLVMGetNamedFunction(module, "main");
    if (!current_function) {
        LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
        current_function = LLVMAddFunction(module, "main", main_type);
        LLVMBasicBlockRef entry = LLVMAppendBasicBlock(current_function, "entry");
        LLVMPositionBuilderAtEnd(builder, entry);
    }

    // Gera o código para a AST
    codegen_node(node);

    // Finaliza a função 'main' se necessário
    LLVMBasicBlockRef last_block = LLVMGetInsertBlock(builder);
    if (!LLVMGetBasicBlockTerminator(last_block)) {
        LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));
    }

    // Verifica a validade do módulo
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &error)) {
        fprintf(stderr, "Erro ao verificar o módulo LLVM: %s\n", error);
        LLVMDisposeMessage(error);
        exit(1);
    }

    // Executa a função 'main'
    int (*main_ptr)() = (int (*)())LLVMGetPointerToGlobal(engine, current_function);
    main_ptr();
    
    // Libera recursos
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
}

/**
 * Função para geração de código com base no tipo do nó da AST.
 * @param node Nó atual da AST.
 * @return Referência LLVMValueRef correspondente.
 */
LLVMValueRef codegen_node(ASTNode *node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_VAR_DECL:
            return codegen_var_decl(node);
        case NODE_ASSIGNMENT:
            return codegen_assignment(node);
        case NODE_PRINT:
            return codegen_print(node);
        case NODE_IF:
            return codegen_if(node);
        case NODE_WHILE:
            return codegen_while(node);
        case NODE_BLOCK:
            codegen_block(node->body);
            return NULL;
        case NODE_BINOP:
            return codegen_binop(node);
        case NODE_NUMBER:
            return codegen_number(node);
        case NODE_IDENTIFIER:
            return codegen_identifier(node);
        default:
            fprintf(stderr, "Erro: Tipo de nó desconhecido %d\n", node->type);
            exit(1);
    }
}

/**
 * Gera código para declaração de variáveis.
 */
LLVMValueRef codegen_var_decl(ASTNode *node) {
    LLVMValueRef func = current_function ? current_function : LLVMGetNamedFunction(module, "main");
    if (!func) {
        fprintf(stderr, "Erro: Declaração de variável fora do contexto de função\n");
        exit(1);
    }

    LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(func);
    LLVMPositionBuilderAtEnd(builder, entry_block);
    LLVMValueRef var_alloc = LLVMBuildAlloca(builder, LLVMInt32Type(), node->identifier);

    named_values[variable_index++] = var_alloc;

    if (node->right) {
        LLVMValueRef value = codegen_node(node->right);
        LLVMBuildStore(builder, value, var_alloc);
    }

    return var_alloc;
}

/**
 * Gera código para atribuições.
 */
LLVMValueRef codegen_assignment(ASTNode *node) {
    LLVMValueRef var_alloc = NULL;
    for (int i = 0; i < variable_index; i++) {
        if (strcmp(LLVMGetValueName(named_values[i]), node->identifier) == 0) {
            var_alloc = named_values[i];
            break;
        }
    }

    if (!var_alloc) {
        fprintf(stderr, "Erro: Variável '%s' não declarada\n", node->identifier);
        exit(1);
    }

    LLVMValueRef value = codegen_node(node->right);
    LLVMBuildStore(builder, value, var_alloc);
    return value;
}

/**
 * Gera código para instruções de impressão.
 */
LLVMValueRef codegen_print(ASTNode *node) {
    LLVMValueRef value = codegen_node(node->right);
    LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
    if (!printf_func) {
        LLVMTypeRef printf_args[] = { LLVMPointerType(LLVMInt8Type(), 0) };
        LLVMTypeRef printf_type = LLVMFunctionType(LLVMInt32Type(), printf_args, 1, 1);
        printf_func = LLVMAddFunction(module, "printf", printf_type);
    }

    LLVMValueRef format_str = LLVMBuildGlobalStringPtr(builder, "%d\n", "format_str");
    LLVMValueRef args[] = { format_str, value };
    LLVMBuildCall2(builder, LLVMFunctionType(LLVMInt32Type(), NULL, 0, 1), printf_func, args, 2, "");
    return NULL;
}

/**
 * Gera código para instruções condicionais (if).
 */
LLVMValueRef codegen_if(ASTNode *node) {
    LLVMValueRef condition = codegen_node(node->condition);

    if (LLVMGetTypeKind(LLVMTypeOf(condition)) != LLVMIntegerTypeKind || 
        LLVMGetIntTypeWidth(LLVMTypeOf(condition)) != 1) {
        condition = LLVMBuildICmp(builder, LLVMIntNE, condition, LLVMConstInt(LLVMInt32Type(), 0, 0), "ifcond");
    }

    LLVMValueRef func = current_function ? current_function : LLVMGetNamedFunction(module, "main");
    LLVMBasicBlockRef then_block = LLVMAppendBasicBlock(func, "then");
    LLVMBasicBlockRef else_block = LLVMAppendBasicBlock(func, "else");
    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(func, "merge");

    LLVMBuildCondBr(builder, condition, then_block, else_block);

    LLVMPositionBuilderAtEnd(builder, then_block);
    codegen_node(node->then_block);
    LLVMBuildBr(builder, merge_block);

    LLVMPositionBuilderAtEnd(builder, else_block);
    if (node->else_block) {
        codegen_node(node->else_block);
    }
    LLVMBuildBr(builder, merge_block);

    LLVMPositionBuilderAtEnd(builder, merge_block);
    return NULL;
}

/**
 * Gera código para loops (while).
 */
LLVMValueRef codegen_while(ASTNode *node) {
    LLVMValueRef func = current_function ? current_function : LLVMGetNamedFunction(module, "main");

    LLVMBasicBlockRef cond_block = LLVMAppendBasicBlock(func, "cond");
    LLVMBasicBlockRef body_block = LLVMAppendBasicBlock(func, "body");
    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(func, "merge");

    LLVMBuildBr(builder, cond_block);

    LLVMPositionBuilderAtEnd(builder, cond_block);
    LLVMValueRef condition = codegen_node(node->condition);

    if (LLVMGetTypeKind(LLVMTypeOf(condition)) != LLVMIntegerTypeKind || 
        LLVMGetIntTypeWidth(LLVMTypeOf(condition)) != 1) {
        condition = LLVMBuildICmp(builder, LLVMIntNE, condition, LLVMConstInt(LLVMInt32Type(), 0, 0), "whilecond");
    }

    LLVMBuildCondBr(builder, condition, body_block, merge_block);

    LLVMPositionBuilderAtEnd(builder, body_block);
    codegen_block(node->body);
    LLVMBuildBr(builder, cond_block);

    LLVMPositionBuilderAtEnd(builder, merge_block);
    return NULL;
}

/**
 * Gera código para operações binárias.
 */
LLVMValueRef codegen_binop(ASTNode *node) {
    LLVMValueRef left = codegen_node(node->left);
    LLVMValueRef right = codegen_node(node->right);

    switch (node->binop) {
        case '+': return LLVMBuildAdd(builder, left, right, "addtmp");
        case '-': return LLVMBuildSub(builder, left, right, "subtmp");
        case '*': return LLVMBuildMul(builder, left, right, "multmp");
        case '/': return LLVMBuildSDiv(builder, left, right, "divtmp");
        case '>': return LLVMBuildICmp(builder, LLVMIntSGT, left, right, "gttmp");
        case '<': return LLVMBuildICmp(builder, LLVMIntSLT, left, right, "lttmp");
        case 'G': return LLVMBuildICmp(builder, LLVMIntSGE, left, right, "getmp");
        case 'L': return LLVMBuildICmp(builder, LLVMIntSLE, left, right, "letmp");
        case '=': return LLVMBuildICmp(builder, LLVMIntEQ, left, right, "eqtmp");
        case '!': return LLVMBuildICmp(builder, LLVMIntNE, left, right, "netmp");
        default:
            fprintf(stderr, "Erro: Operador binário desconhecido '%c'\n", node->binop);
            exit(1);
    }
}

/**
 * Gera código para números literais.
 */
LLVMValueRef codegen_number(ASTNode *node) {
    return LLVMConstInt(LLVMInt32Type(), node->number, 0);
}

/**
 * Gera código para identificadores.
 */
LLVMValueRef codegen_identifier(ASTNode *node) {
    LLVMValueRef var_alloc = NULL;
    for (int i = 0; i < variable_index; i++) {
        if (strcmp(LLVMGetValueName(named_values[i]), node->identifier) == 0) {
            var_alloc = named_values[i];
            break;
        }
    }

    if (!var_alloc) {
        fprintf(stderr, "Erro: Variável '%s' não encontrada\n", node->identifier);
        exit(1);
    }

    return LLVMBuildLoad2(builder, LLVMInt32Type(), var_alloc, node->identifier);
}

/**
 * Gera código para blocos de código.
 */
void codegen_block(ASTNodeList *node_list) {
    ASTNodeList *current = node_list;
    while (current) {
        if (!current->node) {
            fprintf(stderr, "Erro: Nó nulo no bloco\n");
            exit(1);
        }
        codegen_node(current->node);
        current = current->next;
    }
}
