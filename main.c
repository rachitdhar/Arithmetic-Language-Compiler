#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// initializing global variables
static void init() {
    Line = 1;
    Putback = '\n';
}

void main(int argc, char* argv[]) {
    init();

    // open the input file to read it
    if ((Infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    // open the output file to write assembly to it
    if ((Outfile = fopen("out.s", "w")) == NULL) {
        fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
        exit(1);
    }

    scan(&Token);                       // get the first token
    struct ASTnode* n = binexpr(0);     // create the parse AST tree
    printf("%d\n", interpretAST(n));    // print the interpreted value
    generatecode(n);                    // generate assembly to write to output file

    fclose(Outfile);
    exit(0);
}