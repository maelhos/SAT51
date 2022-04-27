#include "quine.h"

bool recquine(clause_list* f, valuation* v, literal l){   
    if (*f == 0)
        return true;

    clause_list fp = copyClauses(*f);
    bool vl = evalAtLiteral(fp, l, true);
    if (!vl){
        free(fp);
        fp = copy(f);
        vl = evalAtLiteral(fp, l, false);
        if (!vl)
            return false;
    }
    if (recquine(fp, l + 1)){
        printf("SAT\n");
        for (uint32_t i = 0; i < f->nbVars; i++){
            if (!f->valuations[i])
                printf("-");
            printf("%d ", i + 1);
        }
        printf("0\n");
        
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
    valuation ret = recquine(&f->clauses, f->valuations, 1);
    return ret;
}