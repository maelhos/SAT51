#include "quine.h"

bool recquine(clause_list* f, valuation* v, uint32_t vsize, literal l, uint64_t cnt){  
    if (*f == 0)
        return true;

    if (l > vsize)
        return false;

    clause_list pcl = *f;
    while (pcl != 0)
    {
        if (pcl->lit1 == 0 && pcl->lit2 == 0 && pcl->lit3 == 0)
            return false;
        pcl = pcl->next;
    }

    clause_list fp = copyClauses(*f);
    eval(&fp, l, true);
    v[l-1] = TRUE;
    if (recquine(&fp, v, vsize, l + 1, cnt + 1)){
        return true;
    }
    else{
        v[l-1] = FALSE;
        free(fp);
        fp = copyClauses(*f);
        eval(&fp, l, false);
        return recquine(&fp, v, vsize, l + 1, cnt + 2);
    }
}

bool quine(formula f){
    bool ret = recquine(&f->clauses, f->valuations, f->nbVars, 1, 0);
    if (!ret)
        flushValuations(f->valuations, f->nbVars);
    return ret;
}