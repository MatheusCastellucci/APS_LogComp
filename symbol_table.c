#include "symbol_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Variable {
    char* name;
    LLVMValueRef value;
    struct Variable* next;
} Variable;

static Variable* variable_list = NULL;

LLVMValueRef get_variable(const char* name) {
    Variable* var = variable_list;
    while (var) {
        if (strcmp(var->name, name) == 0) {
            return var->value;
        }
        var = var->next;
    }
    return NULL;
}

void set_variable(const char* name, LLVMValueRef value) {
    if (!name || !value) {
        fprintf(stderr, "Error: Invalid variable assignment (name or value is null)\n");
        exit(1);
    }

    Variable* var = malloc(sizeof(Variable));
    if (!var) {
        fprintf(stderr, "Error: Memory allocation failed for variable '%s'\n", name);
        exit(1);
    }

    var->name = strdup(name);
    if (!var->name) {
        fprintf(stderr, "Error: Memory allocation failed for variable name '%s'\n", name);
        free(var);
        exit(1);
    }

    var->value = value;
    var->next = variable_list;
    variable_list = var;
}
