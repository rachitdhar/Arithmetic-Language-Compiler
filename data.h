#ifndef extern_
#define extern_ extern
#endif

extern_ int Line;       // line number
extern_ int Putback;    // character to put back (if read too far ahead in input stream)
extern_ FILE* Infile;   // pointer to input file
extern_ FILE* Outfile;   // pointer to output file (to write the assembly code generated)

extern_ struct token Token; // storing the most recent token scanned from input