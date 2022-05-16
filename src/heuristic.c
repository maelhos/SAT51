#include "heuristic.h"


literal chooseLit_FIRST(clause_list cl){
    if (cl->lit1 != 0)
        return abs(cl->lit1);
    else if (cl->lit2 != 0)
        return abs(cl->lit2);
    else if (cl->lit3 != 0)
        return abs(cl->lit3);
    return 0;
}

literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode){
    if (heuristicmode == HEUR_FIRST)
        return chooseLit_FIRST(cl);
    
    clause_list tc = cl;
    
    uint32_t* Cp    = alloca(sizeof(uint32_t) * (vsize+1));
    uint32_t* Cn    = alloca(sizeof(uint32_t) * (vsize+1));
    uint32_t* CpPCn = alloca(sizeof(uint32_t) * (vsize+1));
    uint32_t* CpMCn = alloca(sizeof(uint32_t) * (vsize+1));
    for (uint32_t i = 0; i < vsize; i++){
        Cp[i] = 0;
        Cn[i] = 0;
        CpPCn[i] = 0;
        CpMCn[i] = 0;
    }
    
    while (tc != 0){
        if (tc->lit1 > 0)
            Cp[tc->lit1 - 1]++;
        else 
            Cn[-tc->lit1 - 1]++;
        CpPCn[abs(tc->lit1) - 1]++;
        CpMCn[abs(tc->lit1) - 1] = MAX(Cp[abs(tc->lit1) - 1], Cn[abs(tc->lit1) - 1]);

        if (tc->lit2 > 0)
            Cp[tc->lit2 - 1]++;
        else 
            Cn[-tc->lit2 - 1]++;
        CpPCn[abs(tc->lit2) - 1]++;
        CpMCn[abs(tc->lit2) - 1] = MAX(Cp[abs(tc->lit2) - 1], Cn[abs(tc->lit2) - 1]);

        if (tc->lit3 > 0)
            Cp[tc->lit3 - 1]++;
        else 
            Cn[-tc->lit3 - 1]++;
        CpPCn[abs(tc->lit3) - 1]++;
        CpMCn[abs(tc->lit3) - 1] = MAX(Cp[abs(tc->lit3) - 1], Cn[abs(tc->lit3) - 1]);
        tc = tc->next;
    }
    uint32_t ret = 0;
    uint32_t score = 0;
    switch (heuristicmode)
    {
    case HEUR_RANDOM:{
        literal a = rand() % vsize;
        while (Cp[a] == 0)
            a = rand() % vsize;
        
        return (a+1) % vsize;
        break;
    }
    
    case HEUR_CS:{
        for (uint32_t i = 0; i < vsize; i++)
        {
            if (score < CpPCn[i]){
                ret = i;
                score = CpPCn[i];
            }
        }
        return ret+1;
        break;
    }

    case HEUR_IS:{
        for (uint32_t i = 0; i < vsize; i++)
        {
            if (score < CpMCn[i]){
                ret = i;
                score = CpMCn[i];
            }
        }
        return ret+1;
        break;
    }

    default:
        break;
    }
    
}