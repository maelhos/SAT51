#include "DPLL.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize, literal l){  
    if (l > vsize)
        return false;

    if (!unit_propagate(f, v))
        return false;
    
    if (*f == 0)
        return true;

    clause_list pcl = *f;
    while (pcl != 0)
    {
        if (pcl->lit1 == 0 && pcl->lit2 == 0 && pcl->lit3 == 0)
            return false;
        pcl = pcl->next;
    }

    clause_list fp = copyClauses(*f);

    if (evalCheck(&fp, l)){
        eval(&fp, l);
        v[l-1] = TRUE;

        if (recDPLL(&fp, v, vsize, l + 1)){
            return true;
        }
        else{ // in this cas we only tested for l "positive" so we need to look for "negative" aswell OPTI TODO: make a function that checks if either is available 
            v[l-1] = FALSE;
            free(fp);
            fp = copyClauses(*f);
            eval(&fp, -l);
            return recDPLL(&fp, v, vsize, l + 1);
        }
    }
    else{
        eval(&fp, -l);
        v[l-1] = FALSE;

        if (recDPLL(&fp, v, vsize, l + 1)){
            return true;
        }
        else{
            return false; // in this case we know that neither works
        }
    }    
    
}

bool DPLL(formula f){
    bool ret = recDPLL(&f->clauses, f->valuations, f->nbVars, 1);
    if (!ret)
        flushValuations(f->valuations, f->nbVars);
    return ret;
}