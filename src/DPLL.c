#include "DPLL.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize, uint8_t heurmode){  
    
    clause_list pcl = *f;
    while (pcl != 0)
    {
        if (pcl->lits == 0)
            printf("AAAAAAAAAAAAA\n");
        pcl = pcl->next;
    }
    
    if (!unit_propagate(f, v))
        return false;
        
    if (*f == 0)
        return true;

    literal l = chooseLit(*f, vsize, heurmode);
    clause_list fp = copyClauses(*f);
    bool tret = false;

    v[l-1] = TRUE;
    eval(&fp, l);
    if (recDPLL(&fp, v, vsize, heurmode)){
        clause_clear(fp);
        return true;
    }
    else{ // in this cas we only tested for l "positive" so we need to look for "negative" aswell OPTI TODO: make a function that checks if either is available 
        v[l-1] = FALSE;
        clause_clear(fp);
        fp = copyClauses(*f);
        if (eval(&fp, -l))
            tret = recDPLL(&fp, v, vsize, heurmode);
        clause_clear(fp);
        return tret;
    } 
    
}
bool DPLL(formula f){
    clause_list operating = copyClauses(f->clauses);
    bool ret = recDPLL(&operating, f->valuations, f->nbVars, HEUR_FIRST);
    free(operating);
    if (!ret)
        flushValuations(f->valuations, f->nbVars);
    return ret;
}
/*
timeout = 5s
time in ms
x = no sucess at all
- = some success but still some outime
         | uf20 | uf50 | uf75  | uf100 | uf125 | uf150 | uf175 | uf200 |
QUINE -> | 13.7 |  x   |   x   |   x   |   x   |   x   |   x   |   x   |
FIRST -> |  8.2 |  9.4 |  22.0 | 138.1 |   -   |   x   |   x   |   x   |
RDLIS -> |  8.0 |  9.3 |  14.7 |  42.0 | 211.2 |   -   |   -   |   x   |
RDLCS -> |  8.1 |  8.6 |  11.5 |  23.2 |  91.4 | 323.1 |   -   |   x   |
JW    -> |  8.2 |  8.5 |   9.9 |  15.1 |  36.7 |  96.8 | 387.5 |   -   |


*/