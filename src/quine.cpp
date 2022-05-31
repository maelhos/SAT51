#include "quine.h"

bool recquine(clause_list* f, valuation* v, int32_t vsize, literal l){ 
    if (l > vsize + 1)
        return false;
        
    if (*f == 0)
        return true;  
        
    clause_list pcl = *f;
    while (pcl != 0)
    {
        if (pcl->lits == 0)
            return false;
        pcl = pcl->next;
    }

    clause_list fp = copyClauses(*f);
    naiveval(&fp, l);
    v[l-1] = TRUE;
    if (recquine(&fp, v, vsize, l + 1)){
        clause_clear(fp);
        return true;
    }
    else{
        v[l-1] = FALSE;
        clause_clear(fp);
        fp = copyClauses(*f);
        naiveval(&fp, -l);
        bool tret = recquine(&fp, v, vsize, l + 1);
        clause_clear(fp);
        return tret;
    }
}

bool quine(formula f){
    clause_list operating = copyClauses(f->clauses);
    bool ret = recquine(&operating, f->valuations, f->nbVars, 1);
    clause_clear(operating);
    if (!ret)
        flushValuations(f->valuations, f->nbVars);
    return ret;
}