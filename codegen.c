#include "codegen.h"
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>
#include <stdlib.h>

/* External LLVM variables */
extern LLVMModuleRef module;
extern LLVMBuilderRef builder;
extern LLVMTypeRef int_type;
extern LLVMValueRef current_function;

/* Forward declarations */
void codegen_statement(struct Statement* stmt);
LLVMValueRef get_printf_function();

/* Function to generate code for statements */
void codegen_statements(struct Statements* statements) {
    struct Statements* stmt_list = statements;
    while (stmt_list) {
        struct Statement* stmt = stmt_list->statement;
        if (stmt) {
            codegen_statement(stmt);
        }
        stmt_list = stmt_list->next;
    }
}

/* Function to generate code for a single statement */
void codegen_statement(struct Statement* stmt) {
    if (!stmt) {
        fprintf(stderr, "Error: Null statement encountered\n");
        return;
    }

    switch (stmt->type) {
        case STMT_VARIABLE_DECLARATION:
            {
                char* var_name = stmt->data.variable_declaration.identifier;
                LLVMValueRef init_value = stmt->data.variable_declaration.value;

                if (!var_name) {
                    fprintf(stderr, "Error: Variable declaration with null identifier\n");
                    exit(1);
                }

                if (init_value == NULL) {
                    init_value = LLVMConstInt(int_type, 0, 0);
                }

                LLVMValueRef alloca = LLVMBuildAlloca(builder, int_type, var_name);
                if (!alloca) {
                    fprintf(stderr, "Error: Failed to allocate space for variable '%s'\n", var_name);
                    exit(1);
                }
                LLVMBuildStore(builder, init_value, alloca);

                set_variable(var_name, alloca);
            }
            break;

        case STMT_PRINT_STATEMENT:
            {
                LLVMValueRef expr = stmt->data.print_statement.expression;
                if (!expr) {
                    fprintf(stderr, "Error: Print statement with null expression\n");
                    exit(1);
                }

                LLVMValueRef printf_func = get_printf_function();
                LLVMValueRef format_str = LLVMBuildGlobalStringPtr(builder, "%d\n", "fmt");
                if (!format_str) {
                    fprintf(stderr, "Error: Failed to create format string\n");
                    exit(1);
                }

                LLVMValueRef args[] = { format_str, expr };
                LLVMBuildCall2(
                    builder,
                    LLVMGetElementType(LLVMTypeOf(printf_func)),
                    printf_func,
                    args,
                    2,
                    ""
                );
            }
            break;

        default:
            fprintf(stderr, "Error: Unknown statement type\n");
            exit(1);
    }
}

/* Function to get or declare the printf function */
LLVMValueRef get_printf_function() {
    LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
    if (!printf_func) {
        LLVMTypeRef printf_arg_types[] = { LLVMPointerType(LLVMInt8Type(), 0) };
        LLVMTypeRef printf_type = LLVMFunctionType(
            LLVMInt32Type(),
            printf_arg_types,
            1,
            /* IsVarArg = */ 1
        );
        printf_func = LLVMAddFunction(module, "printf", printf_type);
        if (!printf_func) {
            fprintf(stderr, "Error: Failed to declare 'printf' function\n");
            exit(1);
        }
    }
    return printf_func;
}
