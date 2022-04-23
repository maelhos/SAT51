#include "quine.h"

bool recquine(formula f, literal l){
    if (f->clauses == 0)
        return true;

    formula fp = copy(f);
    bool vl = evalAtLiteral(fp, l, true);
    if (!vl){
        free(fp);
        fp = copy(f);
        vl = evalAtLiteral(fp, l, false);
        if (!vl)
            return false;
    }
    vl = recquine(fp, l + 1);
    if (vl){
        for (uint32_t i = 0; i < f->nbClauses; i++)
            f->valuations[i] = fp->valuations[i];
        free(fp);
        return true;
    }
    else{
        free(fp);
        fp = copy(f);
        vl = evalAtLiteral(fp, l + 1, false);
        return recquine(fp, l + 2);
    }
}

bool quine(formula f){
    valuation ret = recquine(f, 1);
    return ret;
}