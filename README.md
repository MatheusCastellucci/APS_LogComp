# APS_LogComp


## Estruturando a Linguagem Zen em EBNF

Vamos começar definindo os conceitos e características que queremos na linguagem zen:

* Sintaxe Minimalista: Utilizar palavras-chave simples e claras.
* Expressões Naturais: Usar estruturas que se assemelhem à linguagem humana.
* Fluxo de Controle Simples: Facilitar a leitura e compreensão do código.
* Variáveis e Operações Básicas: Permitir manipulação de dados de forma intuitiva.

Palavras-chave Propostas:

* Declarando Variáveis: let
* Atribuição: is
* Condicional: if, else
* Loop: while
* Funções: function, end
* Operadores Lógicos: and, or, not
* Operadores Matemáticos: plus, minus, times, divided by

## Gramática em EBNF:

Vamos agora definir a gramática da linguagem zen em EBNF.

```
<program> ::= { <statement> }

<statement> ::= <variable_declaration> | <assignment> | <function_declaration> | <control_structure> | <expression> ";"

<variable_declaration> ::= "let" <identifier> [ "is" <expression> ] ";"

<assignment> ::= <identifier> "is" <expression> ";"

<function_declaration> ::= "function" <identifier> "(" [ <parameter_list> ] ")" <block> "end"

<parameter_list> ::= <identifier> { "," <identifier> }

<control_structure> ::= <if_statement> | <while_loop>

<if_statement> ::= "if" <expression> <block> [ "else" <block> ] "end"

<while_loop> ::= "while" <expression> <block> "end"

<block> ::= { <statement> }

<expression> ::= <term> { <add_op> <term> }

<term> ::= <factor> { <mul_op> <factor> }

<factor> ::= <number> | <identifier> | "(" <expression> ")" | <function_call>

<function_call> ::= <identifier> "(" [ <argument_list> ] ")"

<argument_list> ::= <expression> { "," <expression> }

<add_op> ::= "plus" | "minus"

<mul_op> ::= "times" | "divided by"

<identifier> ::= <letter> { <letter> | <digit> | "_" }

<number> ::= <digit> { <digit> }

<letter> ::= "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" |
             "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" |
             "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" |
             "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z"

<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```


## Explicação da Gramática 

* **Declaração de Variáveis**: Utilizamos let para declarar variáveis. Opcionalmente, podemos atribuir um valor inicial usando is.

    ```
    let x;
    let y is 10;
    ```

* **Atribuição**: Utilizamos is para atribuir um valor a uma variável.

    ```
    x is y plus 5;
    ```

* **Expressões Matemáticas**: Usamos palavras em vez de símbolos para operações.
    
    ```
    total is x times y;
    ```

* **Estruturas de Controle**: Palavras-chave simples como if, else, while, e encerramos blocos com end.
    
    ```
    if x is greater than y
        x is x minus 1;
    else
        x is x plus 1;
    end
    ```

* **Funções**: Definimos funções com function e encerramos com end.
    
    ```
    function greet(name)
        print "Hello, " plus name;
    end

    ```