# Simple Compiler (in C)

Compiles arithmetic expressions involving any combination of integers and +, -, *, and /.
The command 'make' is used to compile the compiler, and obtain a .exe file named 'comp'.

An input file (say 'input01.txt') contains the arithmetic expression.
It is then compiled by the compiler using the command:

./comp input01.txt

This produces an x86-64 assembly file 'out.s' (and in addition, an output of the value of the
arithmetic expression is also produced independently; this is done by an interpreter - from the
file 'interp.c', which doesn't serve any other purpose, and is not necessary for the working
of the compiler.

## Basic Roles of the Files

The header files:

defs.h : 	contains some important #include libraries, and some structs and enums that are defined
data.h : 	contains global variables that are needed across multiple files of the compiler
		(such as input and output file pointers, etc.)
decl.h :	contains function declarations (prototypes)

Main source code:

main.c :	The main() function is called from here. Reads the input file, and writes assembly
		to the output file.

The Lexer ('Scanner') files - scan.c 		(Reads the input and breaks it into tokens)
The Parser files - expr.c, tree.c, interp.c 	(Uses the tokens to create an Abstract Syntax Tree, based on
								an operator precedence table)
The Compiler files - gen.c, cg.c			(Goes through the AST, and generates the corresponding assembly)