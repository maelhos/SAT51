#include "stdinc.h"
#include "argparsing.h"
#include "parser.h"
#include "quine.h"
#include "DPLL.h"
#include <time.h>

int main(int argc, char** argv){
    arg_state rs = (arg_state)malloc(sizeof(struct _arg_state));
    parseargs(argc, argv, &rs);
    srand(rs->seed);
    FILE* filecnf = fopen(rs->filename, "r");
    if (filecnf == 0)
    {
        printf("CNF file %s not found or does not have permition ...\n", rs->filename);
        free(rs);
        exit(EXIT_FAILURE);
    }
    parser p(filecnf);
    formula f = p.parse();

    //better_formula fp = convert(f);
    //print_better_formula(fp);
    //partial_valuation_stack PVS = 0;
    //better_eval(fp, 1, TRUE, PVS_HEURISTIC_CHOICE, &PVS);
    //printPVS(PVS);
    //print_better_formula(fp);
    //better_eval(fp, 3, TRUE, PVS_HEURISTIC_CHOICE, &PVS);
    //printPVS(PVS);
    //print_better_formula(fp);

    if (rs->algo == ALGO_QUINE){
        quine solver = quine(f, rs->heur);
        solver.run();
    }
    else if (rs->algo == ALGO_DPLL){
        DPLL solver = DPLL(f, rs->heur);
        solver.run();
    }

    for (uint32_t i = 0; i < f.p_nbVars; i++)
        f.p_clauses.beval(i + 1, f.p_valuations[i].p_val);
    
    f.p_clauses.printcl_sat();

    if (f.p_clauses.p_CL->empty())
        valuation::printValAsCNF(f.p_valuations, f.p_nbVars);
    
    free(rs);
    return EXIT_SUCCESS;
}