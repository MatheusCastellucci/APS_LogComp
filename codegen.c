#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>

LLVMModuleRef module;
LLVMBuilderRef builder;
LLVMExecutionEngineRef engine;
LLVMValueRef current_function = NULL;
LLVMValueRef named_values[100];
int variable_index = 0;

// Function declarations
LLVMValueRef codegen_node(ASTNode *node);
LLVMValueRef codegen_var_decl(ASTNode *node);
LLVMValueRef codegen_assignment(ASTNode *node);
LLVMValueRef codegen_print(ASTNode *node);
LLVMValueRef codegen_if(ASTNode *node);
LLVMValueRef codegen_while(ASTNode *node);
LLVMValueRef codegen_binop(ASTNode *node);
LLVMValueRef codegen_number(ASTNode *node);
LLVMValueRef codegen_identifier(ASTNode *node);
void codegen_block(ASTNodeList *node_list); // Updated to process ASTNodeList*

void codegen(ASTNode *node) {
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMLinkInMCJIT();
    char *error = NULL;

    module = LLVMModuleCreateWithName("my_module");
    builder = LLVMCreateBuilder();

    // Set up execution engine
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error) != 0) {
        fprintf(stderr, "Failed to create execution engine: %s\n", error);
        exit(1);
    }

    // Ensure a main function exists
    current_function = LLVMGetNamedFunction(module, "main");
    if (!current_function) {
        LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
        current_function = LLVMAddFunction(module, "main", main_type);
        LLVMBasicBlockRef entry = LLVMAppendBasicBlock(current_function, "entry");
        LLVMPositionBuilderAtEnd(builder, entry);
    }

    // Generate code for the AST
    codegen_node(node);

    // Complete main function if necessary
    LLVMBasicBlockRef last_block = LLVMGetInsertBlock(builder);
    if (!LLVMGetBasicBlockTerminator(last_block)) {
        LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));
    }

    // Verify the module
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &error)) {
        fprintf(stderr, "Error verifying module: %s\n", error);
        LLVMDisposeMessage(error);
        exit(1);
    }

    // Print LLVM IR for debugging
    LLVMDumpModule(module);

    // Execute the main function
    int (*main_ptr)() = (int (*)())LLVMGetPointerToGlobal(engine, current_function);
    int result = main_ptr();
    printf("Program exited with code %d\n", result);

    // Cleanup
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
}


LLVMValueRef codegen_node(ASTNode *node) {
    if (!node) return NULL;

    printf("Debug: Visiting node of type %d\n", node->type);

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
            codegen_block(node->body); // Pass the body (ASTNodeList*) to codegen_block
            return NULL;
        case NODE_BINOP:
            return codegen_binop(node);
        case NODE_NUMBER:
            return codegen_number(node);
        case NODE_IDENTIFIER:
            return codegen_identifier(node);
        default:
            fprintf(stderr, "Error: Unknown node type %d\n", node->type);
            exit(1);
    }
}

LLVMValueRef codegen_var_decl(ASTNode *node) {
    printf("Debug: Generating code for variable declaration '%s'\n", node->identifier);

    // Ensure we are inside a function context
    LLVMValueRef func = current_function ? current_function : LLVMGetNamedFunction(module, "main");
    if (!func) {
        fprintf(stderr, "Error: Variable declaration outside of function context\n");
        exit(1);
    }

    // Create allocation for the variable
    LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(func);
    LLVMPositionBuilderAtEnd(builder, entry_block); // Ensure we position at the function's entry
    LLVMValueRef var_alloc = LLVMBuildAlloca(builder, LLVMInt32Type(), node->identifier);
    
    // Store the allocation in the named_values array
    named_values[variable_index++] = var_alloc;

    // Initialize the variable if an initializer is provided
    if (node->right) {
        LLVMValueRef value = codegen_node(node->right);
        LLVMBuildStore(builder, value, var_alloc);
    }
    
    return var_alloc;
}


LLVMValueRef codegen_assignment(ASTNode *node) {
    printf("Debug: Generating code for assignment to '%s'\n", node->identifier);

    // Find the variable in the named_values array
    LLVMValueRef var_alloc = NULL;
    for (int i = 0; i < variable_index; i++) {
        if (strcmp(LLVMGetValueName(named_values[i]), node->identifier) == 0) {
            var_alloc = named_values[i];
            break;
        }
    }

    if (!var_alloc) {
        fprintf(stderr, "Error: Variable '%s' not declared\n", node->identifier);
        exit(1);
    }

    // Generate the right-hand side value and store it in the variable
    LLVMValueRef value = codegen_node(node->right);
    LLVMBuildStore(builder, value, var_alloc);
    return value;
}

LLVMValueRef codegen_print(ASTNode *node) {
    printf("Debug: Generating code for print statement\n");

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

LLVMValueRef codegen_if(ASTNode *node) {
    printf("Debug: Generating code for if statement\n");

    LLVMValueRef condition = codegen_node(node->condition);
    condition = LLVMBuildICmp(builder, LLVMIntNE, condition, LLVMConstInt(LLVMInt32Type(), 0, 0), "ifcond");

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

LLVMValueRef codegen_while(ASTNode *node) {
    printf("Debug: Generating code for while loop\n");

    // Retrieve the current function or main
    LLVMValueRef func = current_function ? current_function : LLVMGetNamedFunction(module, "main");

    // Create basic blocks for the condition, body, and merge
    LLVMBasicBlockRef cond_block = LLVMAppendBasicBlock(func, "cond");
    LLVMBasicBlockRef body_block = LLVMAppendBasicBlock(func, "body");
    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(func, "merge");

    // Start with a branch to the condition block
    LLVMBuildBr(builder, cond_block);

    // Generate the condition block
    LLVMPositionBuilderAtEnd(builder, cond_block);
    LLVMValueRef condition = codegen_node(node->condition);
    condition = LLVMBuildICmp(builder, LLVMIntNE, condition, LLVMConstInt(LLVMInt32Type(), 0, 0), "whilecond");
    LLVMBuildCondBr(builder, condition, body_block, merge_block);

    // Generate the body block
    LLVMPositionBuilderAtEnd(builder, body_block);
    codegen_block(node->body); // Pass the body (ASTNodeList*) to codegen_block
    LLVMBuildBr(builder, cond_block);

    // Generate the merge block
    LLVMPositionBuilderAtEnd(builder, merge_block);
    return NULL;
}

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
        case 'G': return LLVMBuildICmp(builder, LLVMIntSGE, left, right, "getmp"); // >=
        case 'L': return LLVMBuildICmp(builder, LLVMIntSLE, left, right, "letmp"); // <=
        case '=': return LLVMBuildICmp(builder, LLVMIntEQ, left, right, "eqtmp");
        case '!': return LLVMBuildICmp(builder, LLVMIntNE, left, right, "netmp");
        default:
            fprintf(stderr, "Unknown binary operator '%c'\n", node->binop);
            exit(1);
    }
}

LLVMValueRef codegen_number(ASTNode *node) {
    printf("Debug: Generating code for number %d\n", node->number);
    return LLVMConstInt(LLVMInt32Type(), node->number, 0);
}

LLVMValueRef codegen_identifier(ASTNode *node) {
    printf("Debug: Generating code for identifier '%s'\n", node->identifier);

    // Find the variable in named_values
    LLVMValueRef var_alloc = NULL;
    for (int i = 0; i < variable_index; i++) {
        if (strcmp(LLVMGetValueName(named_values[i]), node->identifier) == 0) {
            var_alloc = named_values[i];
            break;
        }
    }

    if (!var_alloc) {
        fprintf(stderr, "Error: Variable '%s' not found\n", node->identifier);
        exit(1);
    }

    // Load the variable value
    return LLVMBuildLoad2(builder, LLVMInt32Type(), var_alloc, node->identifier);
}

void codegen_block(ASTNodeList *node_list) { // Corrected to process ASTNodeList*
    printf("Debug: Generating code for block\n");

    ASTNodeList *current = node_list;
    while (current) {
        codegen_node(current->node); // Passes ASTNode*, not ASTNodeList*
        current = current->next;
    }
}
