#ifndef CODEGEN_H
#define CODEGEN_H

#include "symbol_table.h"
#include <llvm-c/Core.h>

void codegen_statements(struct Statements* statements);
void codegen_statement(struct Statement* stmt);

#endif /* CODEGEN_H */
