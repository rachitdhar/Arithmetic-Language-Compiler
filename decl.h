
/* function declarations */
/* contains function prototypes for all compiler files */

int scan(struct token* t);

struct ASTnode* mkastnode(int op, struct ASTnode* left, struct ASTnode* right, int intvalue);
struct ASTnode* mkastleaf(int op, int intvalue);
struct ASTnode* mkastunary(int op, struct ASTnode* left, int intvalue);
struct ASTnode* binexpr(int ptp);
int interpretAST(struct ASTnode* n);

void cgpreamble();
void cgpostamble();
void cgprintint(int reg);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
int cgload(int value);
void generatecode(struct ASTnode* n);