#include "stdinc.h"
#include "argparsing.h"
#include "parser.h"
#include "quine.h"
#include "DPLL.h"
#include <time.h>
#include "watchedDPLL.h"

int main(int argc, char* argv[]){
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
    //f.p_clauses.unit_propagate(...) UNIT PROP BEFORE CONVERT
    watchedformula wf(f);
    wf.print();
    int32_t fclause = 0;
    std::vector<partialFrame>* stack = new std::vector<partialFrame>;
    while (true){
        fclause = wf.findBasicUnit();
        if (fclause){
            if (!wf.eval(fclause, stack, PF_CHOICE))
                return false;
        }
        else
            break;
    }
    wf.print();
    std::cout << (int)wf.eval(2, stack, PF_CHOICE);
    wf.print();
    //watchedDPLL solver = watchedDPLL(wf, WHEUR_FIRST);
    //solver.run();
    //for (uint32_t i = 0; i < f.p_nbVars; i++)
    //    f.p_clauses.beval(i + 1, wf.state[i]);
    
    //f.p_clauses.printcl_sat();

    //valuation::printValAsCNF(f.p_valuations, f.p_nbVars);

    exit(0);
    /*
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
    
    */
    free(rs);
    return EXIT_SUCCESS;
}