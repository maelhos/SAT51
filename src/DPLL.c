#include "DPLL.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize, uint8_t heurmode){  
    if (!unit_propagate(f, v))
        return false;
        
    if (*f == 0)
        return true;

    literal l = chooseLit(*f, vsize, heurmode);
    clause_list fp = copyClauses(*f);
    bool tret = false;
    if (evalCheck(&fp, l)){
        v[l-1] = TRUE;
        eval(&fp, l);
        if (recDPLL(&fp, v, vsize, heurmode)){
            free(fp);
            return true;
        }
        else{ // in this cas we only tested for l "positive" so we need to look for "negative" aswell OPTI TODO: make a function that checks if either is available 
            v[l-1] = FALSE;
            free(fp);
            fp = copyClauses(*f);
            if (eval(&fp, -l))
                tret = recDPLL(&fp, v, vsize, heurmode);
            free(fp);
            return tret;
        }
    }
    else{
        v[l-1] = FALSE;
        if (eval(&fp, -l))
            tret = recDPLL(&fp, v, vsize, heurmode);
        free(fp);
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
QUINE -> | 10.1 |  x   |   x   |   x   |   x   |   x   |   x   |   x   |
FIRST -> |  8.2 |  9.4 |  22.0 | 138.1 |   -   |   x   |   x   |   x   |
RDLIS -> |  8.0 |  9.3 |  14.7 |  42.0 | 211.2 |   -   |   -   |   x   |
RDLCS -> |  8.1 |  8.6 |  11.5 |  23.2 |  91.4 | 323.1 |   -   |   x   |
JW    -> |  8.9 |  9.2 |  10.7 |  15.8 |  37.8 | 100.2 | 394.5 |   -   |


*/