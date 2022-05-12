#include "valuation.h"

valuation* initValuations(uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    flushValuations(ret, nbVars);
    return ret;
}

valuation* copyValuations(valuation* vp, uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    for (uint32_t i = 0; i < nbVars; i++)
        ret[i] = vp[i];
    return ret;
}

void flushValuations(valuation* v, uint32_t nbVars){
    for (uint32_t i = 0; i < nbVars; i++)
        v[i] = UNKNOWN;
}

void printValAsCNF(valuation* v, uint32_t nb){
    for (uint32_t i = 0; i < nb; i++)
    {
        if (v[i] == FALSE)
            printf("-");
        else if (v[i] == UNKNOWN){
            printf("? ");
            continue;
        }
        printf("%d ",i+1);
    }
    printf("\n"); 
}

void printValuation(valuation v){
    switch (v)
    {
    case FALSE:
        printf("FALSE");
        break;
    case TRUE:
        printf("TRUE");
        break;
    case UNKNOWN:
        printf("UNKNOWN");
        break;
    default:
        break;
    }
}

literal nextLit(valuation* v, literal l, uint32_t vsize){
    if (l > vsize + 1)
        return l + 1;
    literal ret = l + 1;
    while (v[ret] != UNKNOWN)
        ret++;
    return ret;
}