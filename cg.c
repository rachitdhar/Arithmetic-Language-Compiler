#include "defs.h"
#include "data.h"
#include "decl.h"

/* functions to generate actual assembly code */

static char* reglist[4] = { "%r8", "%r9", "%r10", "%r11" }; // table of strings with
                                                            // actual register names
static int freereg[4];  // 0 -> means not free
                        // 1 -> means free

// makes all registers available
void freeall_registers(void) {
    freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

// free a register
static void free_register(int reg) {
    if (freereg[reg] != 0) {
        fprintf(stderr, "Error trying to free register %d\n", reg);
        exit(1);
    }
    freereg[reg] = 1;
}

// allocate a register
static int alloc_register(void) {
    for (int i = 0; i < 4; i++) {
        if (freereg[i]) {
            freereg[i] = 0;
            return i;
        }
    }
    fprintf(stderr, "Out of registers!\n");
    exit(1);
}

// Loading a register
// generating assembly code to load a register with an int literal
// and return the number of the register
int cgload(int value) {
    int r = alloc_register();   // get a new register
    fprintf(Outfile, "\tmovq\t$%d, %s\n", value, reglist[r]);       //  movq    $VAL, REG
    return r;
}

// preamble assembly code
// NOTE: fputs() can write the '%' character as an ordinary character (i.e. no need to use "%%")
void cgpreamble() {
    freeall_registers();
    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "printint:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf@PLT\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n"
        "\tpushq\t%rbp\n"
        "\tmovq	%rsp, %rbp\n",
        Outfile
    );
}

// postamble assembly code
void cgpostamble() {
    fputs(
        "\tmovl\t$0, %eax\n"
        "\tpopq\t%rbp\n"
        "\tret\n",
        Outfile
    );
}

// Adding two registers
// and returning the number of the register having the result
int cgadd(int r1, int r2) {
    fprintf(Outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]); //  addq    REG1, REG2
    free_register(r1);
    return r2;
}

// Subtracting register r2 from register r1
// and returning the number of the register having the result
int cgsub(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]); //  subq    REG2, REG1
    free_register(r2);
    return r1;
}

// Multiplying two registers
// and returning the number of the register having the result
int cgmul(int r1, int r2) {
    fprintf(Outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]); // imulq   REG1, REG2
    free_register(r1);
    return r2;
}

// Dividing register r1 by register r2
// and returning the number of the register having the result
int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tmovq\t%s, %%rax\n", reglist[r1]);           //  movq    REG1, %rax
    fprintf(Outfile, "\tcqo\n");                                    //  cqo
    fprintf(Outfile, "\tidivq\t%s\n", reglist[r2]);                 //  idivq   REG2
    fprintf(Outfile, "\tmovq\t%%rax, %s\n", reglist[r1]);           //  movq    %rax, REG1
    free_register(r2);
    return r1;
}

// x86-64 does NOT contain any instruction to print a decimal number
// thus, we have written a function called printint() in the preamble assembly (which uses printf)
// we will call it using this function below
void cgprintint(int reg) {
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", reglist[reg]);          //  movq    REG, %rdi
    fprintf(Outfile, "\tcall\tprintint\n");                         //  call    printint
    free_register(reg);
}