#include "stdinc.h"
#include "argparsing.h"
#include "parser.h"
#include "watchedDPLL.h"



int main(int argc, char* argv[]){
    printf(GREEN "[+] Starting Test Run...\n" NC);
    arg_state rs = (arg_state)malloc(sizeof(struct _arg_state));
    parseargs(argc, argv, &rs);
    srand(rs->seed);
    FILE* filecnf = fopen(rs->filename, "r");
    if (filecnf == 0)
    {
        printf(RED "[!] CNF file %s not found or does not have permition ...\n" NC, rs->filename);
        free(rs);
        exit(EXIT_FAILURE);
    }
    parser p(filecnf);
    printf(GREEN "[+] Opened file %s succesfully...\n" NC, rs->filename);
    formula f = p.parse();
    printf(GREEN "[+] Parsed succesfully...\n" NC);
    f.print_formula();
    printf(GREEN "[+] Unit progag ...\n" NC);
    f.p_clauses.unit_propagate(f.p_valuations);
    f.p_nbClauses = f.p_clauses.p_CL->size(); // dont forget to change nb of clauses ...

    f.print_formula();
    formula* fp = f.copy();

    watchedformula wf(f);
    wf.print();
    watchedDPLL wdpl(wf, HEUR_FIRST);

    wdpl.run();

    for (uint32_t i = 0; i < f.p_nbVars; i++)
        f.p_clauses.beval(i + 1, f.p_valuations[i]);
        
    f.print_formula();
    return 0;
}