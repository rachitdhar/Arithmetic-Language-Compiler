#include "defs.h"
#include "decl.h"

/* Assembly Code Generator */

// to calculate expression for AST recursively
static int genAST(struct ASTnode* n) {
    int leftreg, rightreg;

    if (n->left) leftreg = genAST(n->left);
    if (n->right) rightreg = genAST(n->right);

    switch (n->op) {
        case A_ADD: return cgadd(leftreg, rightreg);
        case A_SUBTRACT: return cgsub(leftreg, rightreg);
        case A_MULTIPLY: return cgmul(leftreg, rightreg);
        case A_DIVIDE: return cgdiv(leftreg, rightreg);
        case A_INTLIT: return cgload(n->intvalue);
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->op);
            exit(1);
    }
}

// to generate assembly code
void generatecode(struct ASTnode* n) {
    int reg;

    cgpreamble();       // leading code (preamble)
    reg = genAST(n);    // calculating the expression
    cgprintint(reg);    // code to print the register with the result as int
    cgpostamble();      // trailing code (postamble)
}