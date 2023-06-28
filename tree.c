#include "defs.h"
#include "data.h"
#include "decl.h"

/* contains functions regarding AST trees (for the PARSER) */

// function to build AST node, assign values to its fields,
// and return a pointer to the node
struct ASTnode* mkastnode(int op, struct ASTnode* left, struct ASTnode* right, int intvalue) {
    struct ASTnode* n;

    // malloc a new AST node
    n = (struct ASTnode*) malloc(sizeof(struct ASTnode));

    if (n == NULL) {
        fprintf(stderr, "Unable to malloc in mkastnode()\n");
        exit(1);
    }

    // copy the field values into the node
    n->op = op;
    n->left = left;
    n->right = right;
    n->intvalue = intvalue;
    return n;
}

// function to make a leaf node
struct ASTnode* mkastleaf(int op, int intvalue) {
    return mkastnode(op, NULL, NULL, intvalue);
}

// function to make an ASTnode with only one child
struct ASTnode* mkastunary(int op, struct ASTnode* left, int intvalue) {
    return mkastnode(op, left, NULL, intvalue);
}