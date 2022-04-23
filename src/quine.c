#include "quine.h"

bool recquine(formula f, literal l){
    if (f->clauses == 0)
        return true;

    formula fp = copy(f);
    valuation vl = evalAtLiteral(fp, l, true);
    switch (vl)
    {
    case TRUE:
        for (uint32_t i = 0; i < f->nbVars; i++)
            f->valuations[i] = fp->valuations[i];
        return true;
        break;
    
    case FALSE:
        free(fp);
        fp = copy(f);
        vl = evalAtLiteral(fp, l, false);
        switch (vl)
        {
        case TRUE:
            for (uint32_t i = 0; i < f->nbVars; i++)
                f->valuations[i] = fp->valuations[i];
            free(fp);
            return true;
            break;
        
        case FALSE:
            free(fp);
            return false;
            break;
        default:
            break;
        }
    default:
        break;
    }
    // case UNKNOWN for both
    bool r = recquine(fp, l+1);
    for (uint32_t i = 0; i < f->nbVars; i++)
        f->valuations[i] = fp->valuations[i];
    free(fp);
    return r;
    
}

bool quine(formula f){
    valuation ret = recquine(f, 1);
    return ret;
}