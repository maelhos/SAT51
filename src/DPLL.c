#include "DPLL.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize){  

    if (!unit_propagate(f, v))
        return false;
    

    if (*f == 0)
        return true;

    literal l = chooseLit_FIRST(f);
    clause_list fp = copyClauses(*f);
    bool tret = false;
    if (evalCheck(&fp, l)){
        v[l-1] = TRUE;
        eval(&fp, l);
        if (recDPLL(&fp, v, vsize)){
            free(fp);
            return true;
        }
        else{ // in this cas we only tested for l "positive" so we need to look for "negative" aswell OPTI TODO: make a function that checks if either is available 
            v[l-1] = FALSE;
            free(fp);
            fp = copyClauses(*f);
            if (eval(&fp, -l))
                tret = recDPLL(&fp, v, vsize);
            free(fp);
            return tret;
        }
    }
    else{
        v[l-1] = FALSE;
        if (eval(&fp, -l))
            tret = recDPLL(&fp, v, vsize);
        free(fp);
        return tret;
    }    
    
}

bool DPLL(formula f){
    clause_list operating = copyClauses(f->clauses);
    bool ret = recDPLL(&operating, f->valuations, f->nbVars);
    free(operating);
    if (!ret)
        flushValuations(f->valuations, f->nbVars);
    return ret;
}