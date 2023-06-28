#include "defs.h"
#include "data.h"
#include "decl.h"

/* --------- Code related to PARSER --------- */

// operator precedence for tokens
static int OpPrec[] = { 0, 10, 10, 20, 20,    0 };
//          tokens ->  EOF  +   -   *   /   INTLIT

// getting operator precedence for a token (corresponding to an operator)
static int op_precedence(int tokentype) {
    int prec = OpPrec[tokentype];
    if (prec == 0) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
        exit(1);
    }
    return prec;
}

// converting tokens to AST node operation values
int arithop(int tok) {
    switch (tok) {
        case T_PLUS:    return A_ADD;
        case T_MINUS:   return A_SUBTRACT;
        case T_STAR:    return A_MULTIPLY;
        case T_SLASH:   return A_DIVIDE;
        default:
            fprintf(stderr, "Unknown token in arithop() on line %d\n", Line);
            exit(1);
    }
}

// function to check if current token is INTLIT, and creating a node with it (which is returned)
// and then scanning the next token
struct ASTnode* primary(void) {
    struct ASTnode* n;

    switch (Token.token) {
        case T_INTLIT:
            n = mkastleaf(A_INTLIT, Token.intvalue);
            scan(&Token);
            return n;
        default:
            fprintf(stderr, "Syntax error on line %d\n", Line);
            exit(1);
    }
}

// the parser, that builds the AST tree and returns it -- uses 'Pratt Parsing'
// ptp : 'Previous Token Precedence'
struct ASTnode* binexpr(int ptp) {
    struct ASTnode *left, *right;

    left = primary();   // to get INTLIT value into 'left' node, and also scan next token
    
    int tokentype = Token.token;
    if (tokentype == T_EOF) return left;  // if no tokens remaining, return left node itself

    while (op_precedence(tokentype) > ptp) {
        scan(&Token);       // get next token

        right = binexpr(OpPrec[tokentype]);                     // 'right' node recursively obtained
        left = mkastnode(arithop(tokentype), left, right, 0);   // create new node

        tokentype = Token.token;
        if (tokentype == T_EOF) return left;
    }
    return left;
}