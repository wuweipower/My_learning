#### what is compiler

- compilers are computer programs that translate one language to another one.

- source program(C C++ etc.)->compiler->target program(machine code, assembly language)

#### interpreter and compiler

**same:** 

they are all language implementing system

**difference:** 

- interpreter executes the source program during translation 

- compiler generates object code that is executed after translation completes



source program -> preprocessor ->source program -> compiler->assembly language -> assembler-> relocatable machine code ->loader/linker -> absolute machine code



scanner -> parser -> semantic analysis -> source code optimizer -> code generator -> target code optimizer 



#### 1. Scanner(lexical analysis)

- the task is reading the source program as a file of characters and dividing it into meaningful units called tokens

- each token is a sequence of characters that represents a unit of information in the source program. Tokens have several categories: identifier, keyword, number, operator, special symbol. (Kind, Value)

#### 2. Parser(syntax analysis)

- receives the source code in the form of tokens, generate a parse tree or syntax tree

#### 3. Semantic analyzer

- static semantic: properties of a program that can be determined prior to execution. Including(declaration, type checking)
- dynamic semantic: properties of a program that can be only determined by execution.

1. semantic analysis is realized by symbol table. Attributes are entered symbol table

2. Semantic analyzer will produce an annotated tree. Attributes are added to the tree as annotations

#### 4. Source code optimizer

Only depend on the source code

- some optimizations can be performed directly on the syntax tree
- it is easier to optimize using intermediate code

- intermediate code:  form of code representation intermediate between source code and object code. structure is simple, meaning is clear, and it is easy to translate them to object code

##### IR(intermediate representation)

Any internal representation for the source code used by the compiler is called IR.

The syntax tree and intermediate code are all IR.

#### 5. Code generator

- The code generator takes the IR and generates code for the target machine
- Usually use assembly language as target code
- It is related to the properties of target machine: the number
  of registers, addressing mode, data representation and so on.

#### 6. Target code optimizer

This Optimization includes
• Change addressing mode to improve performance
• Replace slow instructions by faster ones
• Eliminate redundant or unnecessary operations



#### 7. Auxiliary components

literal table

- store constants and strings
- reduce the size of program in memory by allowing the reuse of constants and strings

symbol table

- keeps information associated to identifiers, function, variables constants, data type identifiers

error handler

- detect errors
- generate meaningful error message and resume(恢复) compilation after each error



#### Analysis

scanner, parser, semantic analysis

#### Synthesis

intermediate code generation, intermediate code optimization, target code optimization, target code generation

#### front end & back end

前端包括词法，语法，语义， 源码优化

后端只与目标语言有关，包括代码生成和目标代码优化

Compiler may repeat one or more passes before generating target code

A typical arrangement is one pass for scanning and parsing, one pass for semantic analysis and source-level optimization, and a third pass for code generation and target level optimization.

How many times depend on the source language and the target machine