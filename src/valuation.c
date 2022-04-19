#include "valuation.h"

valuation* initValuations(uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    for (uint32_t i = 0; i < nbVars; i++)
        ret[i] = UNKNOWN;
    return ret;
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