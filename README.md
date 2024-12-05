
# Sensei Language

Sensei é uma linguagem de programação minimalista e educacional, projetada para ensinar conceitos fundamentais de programação e compiladores. A linguagem possui uma sintaxe simples e intuitiva, ideal para iniciantes.

- [Vídeo de Explicação](https://youtu.be/lIBEOEwmkVQ)

## Funcionalidades da Linguagem

A Sensei suporta as seguintes funcionalidades:
- **Declaração de variáveis**:
  - Com ou sem valor inicial (`let x;` ou `let x is 10;`).
- **Atribuições**:
  - Modificar valores de variáveis (`x is x + 1;`).
- **Operações aritméticas e relacionais**:
  - Operadores suportados: `+`, `-`, `*`, `/`, `>`, `<`, `>=`, `<=`, `==`, `!=`.
- **Estruturas condicionais**:
  - `if` com suporte a `else`.
- **Laços de repetição**:
  - `while` com uma condição.
- **Impressão de valores**:
  - `print x;` para exibir valores.

## Estrutura do Projeto

O projeto está organizado nos seguintes arquivos:

- **`lexer.l`**: Define o analisador léxico da linguagem. Responsável por identificar os tokens da linguagem, como palavras-chave, identificadores e operadores.
- **`parser.y`**: Contém o analisador sintático, que constrói a Árvore de Sintaxe Abstrata (AST) a partir dos tokens gerados pelo léxico.
- **`ast.h` e `ast.c`**: Define e implementa as estruturas e funções para a AST.
- **`codegen.h` e `codegen.c`**: Responsáveis pela geração de código LLVM a partir da AST.
- **`Makefile`**: Automatiza a compilação do projeto, incluindo o léxico, parser e código de geração.

Exemplos de testes para a linguagem estão localizados na pasta `testes`.

## EBNF da Sensei

A gramática da Sensei é descrita abaixo:

```ebnf
PROGRAM = { STATEMENT } ;

STATEMENT = VARIABLE_DECLARATION | ASSIGNMENT | PRINT | IF | WHILE | BLOCK ;

VARIABLE_DECLARATION = "let", IDENTIFIER, [ "is", EXPRESSION ], ";" ;

ASSIGNMENT = IDENTIFIER, "is", EXPRESSION, ";" ;

PRINT = "print", EXPRESSION, ";" ;

IF = "if", EXPRESSION, BLOCK, [ "else", BLOCK ] ;

WHILE = "while", EXPRESSION, BLOCK ;

BLOCK = "{", { STATEMENT }, "}" ;

EXPRESSION = TERM, { ( "+" | "-" | ">" | "<" | ">=" | "<=" | "==" | "!=" ), TERM } ;

TERM = FACTOR, { ( "*" | "/" ), FACTOR } ;

FACTOR = NUMBER | IDENTIFIER | "(", EXPRESSION, ")" ;

IDENTIFIER = LETTER, { LETTER | DIGIT } ;

NUMBER = DIGIT, { DIGIT } ;

LETTER = ( "a" | ... | "z" | "A" | ... | "Z" ) ;

DIGIT = ( "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ) ;
```

## Como Compilar e Usar

### Pré-requisitos

- **Flex**: Para gerar o analisador léxico.
- **Bison**: Para gerar o analisador sintático.
- **LLVM**: Para geração de código.

### Build do Projeto

Para limpar os arquivos gerados durante a compilação, execute:

```bash
make clean
```

Execute o comando `make` na raiz do projeto:

```bash
make
```

Isso irá gerar o executável `sensei`.

### Usando a Linguagem

1. Escreva um programa Sensei em um arquivo com extensão `.sns`.
2. Para executar o programa, use o seguinte comando:

```bash
./sensei caminho/do/arquivo.sns
```

Por exemplo:

```bash
./sensei testes/exemplo.sns
```

## Desenvolvedores

- Matheus Castellucci
- Rodrigo Medeiros
