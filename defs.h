#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ------------ For the LEXER ------------- */

// token structure
struct token {
    int token;
    int intvalue;
};

// tokens
enum {
    T_EOF,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_INTLIT
};

/* ----------- For the PARSER ------------ */

// AST node types (AST: Abstract Syntax Tree)
enum {
    A_ADD,
    A_SUBTRACT,
    A_MULTIPLY,
    A_DIVIDE,
    A_INTLIT
};

// AST tree node structure
struct ASTnode {
    int op;                     // operator (add, sub, ... or just A_INTLIT)
    struct ASTnode* left;       // left child node
    struct ASTnode* right;      // right child node
    int intvalue;               // if op is A_INTLIT, stores the integer value
};