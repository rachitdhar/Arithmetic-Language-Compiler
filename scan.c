#include "defs.h"
#include "data.h"
#include "decl.h"

/* contains functions for lexical scanner */

// to get next character from input stream
static int next(void) {
    int c;

    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);  // read from input file
    if (c == '\n') Line++;
    return c;
}

// to putback character to input stream
static void putback(int c) {
    Putback = c;
}

// skipping over whitespace
static int skip(void) {
    int c;

    do {
        c = next();
    } while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');

    return c;
}

// returns position of c in string s; if c not found in s, returns -1
static int chrpos(char* s, int c) {
    char* p;
    p = strchr(s, c); // address of c is stored in p
    return (p ? p - s : -1);
}

// to scan an integer literal
static int scanint(int c) {
    int k, val = 0;

    while ((k = chrpos("0123456789", c)) >= 0) {
        val = (val * 10) + k;
        c = next();
    }

    putback(c); // since the last next() read a non-integer, we must put it
                // back into the input stream so that it can be read again later
    return val;
}

// lexical scanner
// scans and returns the next token found (returns 0 if no token left)
int scan(struct token* t) {
    int c;
    c = skip(); // skip whitespace

    switch (c) {
        case EOF:
            t->token = T_EOF;
            return 0;
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        default:
            if (isdigit(c)) {
                t->token = T_INTLIT;
                t->intvalue = scanint(c); // to scan the integer value from character c
                break;
            }

            printf("Unrecognised character %c on line %d", c, Line);
            exit(1);
    }
    return 1;
}