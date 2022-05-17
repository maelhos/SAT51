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
    bool ret = recDPLL(&operating, f->valuations, f->nbVars, HEUR_JW);
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
         | uf20 | uf50 | uf75  | uf100 | uf125 |
QUINE -> | 10.1 |  x   |   x   |   x   |   x   |
FIRST -> | 10.4 | 49.6 |   x   |   x   |   x   |
RDLCS -> | 10.2 | 22.7 | 318.8 |   x   |   x   |
RDLIS -> | 10.2 | 29.1 | 673.3 |   x   |   x   |
JW    -> |  9.6 | 12.6 |  43.4 | 269.9 |   -   |


*/