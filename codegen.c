#include <stdio.h>
#include "ast.h"
#include "codegen.h"
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>

LLVMModuleRef module;
LLVMBuilderRef builder;
LLVMExecutionEngineRef engine;
LLVMValueRef function;

void codegen(ASTNode *node) {
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    char *error = NULL;
    module = LLVMModuleCreateWithName("my_module");
    builder = LLVMCreateBuilder();
    LLVMLinkInMCJIT();

    // Set up execution engine
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error) != 0) {
        fprintf(stderr, "Failed to create execution engine\n");
        exit(1);
    }

    // Generate code for the AST
    codegen_node(node);

    // Verify the module
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &error)) {
        fprintf(stderr, "Error verifying module: %s\n", error);
        LLVMDisposeMessage(error);
        exit(1);
    }

    // Run the main function
    LLVMValueRef main_func = LLVMGetNamedFunction(module, "main");
    if (!main_func) {
        fprintf(stderr, "No main function found\n");
        exit(1);
    }
    int (*main_ptr)() = (int (*)())LLVMGetPointerToGlobal(engine, main_func);
    int result = main_ptr();
    printf("Program exited with code %d\n", result);

    // Clean up
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
}

void codegen_node(ASTNode *node) {
    if (!node) return;

    // Placeholder implementation: Print the node type
    switch (node->type) {
        case NODE_VAR_DECL:
            printf("Generating code for variable declaration\n");
            break;
        case NODE_ASSIGNMENT:
            printf("Generating code for assignment\n");
            break;
        case NODE_FUNCTION:
            printf("Generating code for function\n");
            break;
        case NODE_FUNCTION_CALL:
            printf("Generating code for function call\n");
            break;
        case NODE_IF:
            printf("Generating code for if statement\n");
            break;
        case NODE_WHILE:
            printf("Generating code for while loop\n");
            break;
        case NODE_PRINT:
            printf("Generating code for print statement\n");
            break;
        case NODE_RETURN:
            printf("Generating code for return statement\n");
            break;
        case NODE_BINOP:
            printf("Generating code for binary operation\n");
            break;
        case NODE_NUMBER:
            printf("Generating code for number: %d\n", node->number);
            break;
        case NODE_IDENTIFIER:
            printf("Generating code for identifier: %s\n", node->identifier);
            break;
        default:
            printf("Unknown node type\n");
    }
}

