#include "valuation.h"


valuation v_negate(valuation v){
    switch (v)
    {
    case TRUE:
        return (FALSE);
        break;
    case FALSE:
        return (TRUE);
        break;
    case UNKNOWN:
        return (UNKNOWN);
        break;
    default:
        return (UNKNOWN);
        break;
    }
    return (UNKNOWN);
}

valuation* v_initValuations(uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    v_flushValuations(ret, nbVars);
    return ret;
}

valuation* v_copyValuations(valuation* vp, uint32_t nbVars){
    valuation* ret = (valuation*)malloc(nbVars * sizeof(valuation));
    for (uint32_t i = 0; i < nbVars; i++)
        ret[i] = vp[i];
    return ret;
}

void v_flushValuations(valuation* v, uint32_t nbVars){
    for (uint32_t i = 0; i < nbVars; i++)
        v[i] = UNKNOWN;
}

void v_printValAsCNF(valuation* v, uint32_t nb){
    for (uint32_t i = 0; i < nb; i++)
    {
        if (v[i] == FALSE)
            printf("-");
        else if (v[i] == UNKNOWN){
            printf("? ");
            continue;
        }
        printf("%d ",i + 1);
    }
    printf("\n"); 
}

void v_printValuation(valuation v){
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

char v_valtochar(valuation v){
    switch (v)
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