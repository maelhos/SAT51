#include "valuation.h"

valuation::valuation(uint8_t val) : p_val(val)
{}

valuation::~valuation(){
}

valuation valuation::negate(){
    switch (p_val)
    {
    case TRUE:
        return valuation(FALSE);
        break;
    case FALSE:
        return valuation(TRUE);
        break;
    case UNKNOWN:
        return valuation(UNKNOWN);
        break;
    default:
        return valuation(UNKNOWN);
        break;
    }
    return valuation(UNKNOWN);
}

valuation* valuation::initValuations(uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    flushValuations(ret, nbVars);
    return ret;
}

valuation* valuation::copyValuations(valuation* vp, uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    for (uint32_t i = 0; i < nbVars; i++)
        ret[i] = vp[i];
    return ret;
}

void valuation::flushValuations(valuation* v, uint32_t nbVars){
    for (uint32_t i = 0; i < nbVars; i++)
        v[i] = UNKNOWN;
}

void valuation::printValAsCNF(valuation* v, uint32_t nb){
    for (uint32_t i = 0; i < nb; i++)
    {
        if (v[i].p_val == FALSE)
            printf("-");
        else if (v[i].p_val == UNKNOWN){
            printf("? ");
            continue;
        }
        printf("%d ",i+1);
    }
    printf("\n"); 
}

void valuation::printValuation(){
    switch (p_val)
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

char valuation::valtochar(){
    switch (p_val)
    {
    case TRUE:
        return '1';
        break;
    case FALSE:
        return '0';
        break;
    case UNKNOWN:
        return 'U';
        break;
    default:
        return 'U';
        break;
    }
    return 'E';
}