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
inline uint32_t normalize(uint32_t a){
    if (a)
        return 1;
    else
        return 0;
    
}
literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode){
    if (heuristicmode == HEUR_FIRST)
        return chooseLit_FIRST(cl);
    clause_list tc = cl;
    
    uint32_t* Cp    = alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* Cn    = alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* CpPCn = alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* CpMCn = alloca(sizeof(uint32_t) * (vsize + 1));
    float*    J     = alloca(sizeof(float) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++){
        Cp[i] = 0;
        Cn[i] = 0;
        CpPCn[i] = 0;
        CpMCn[i] = 0;
        J[i] = 0.0f;
    }
    uint32_t numberofclause = 0;
    while (tc != 0){
        uint32_t clauselen = normalize(tc->lit1) + normalize(tc->lit2) + normalize(tc->lit3);
        if (tc->lit1 != 0){ 
            if (tc->lit1 > 0)
                Cp[tc->lit1 - 1]++;
            else 
                Cn[-tc->lit1 - 1]++;
            J[abs(tc->lit1) - 1] += powf(2.0f, -(float)clauselen);
            CpPCn[abs(tc->lit1) - 1]++;
            CpMCn[abs(tc->lit1) - 1] = MAX(Cp[abs(tc->lit1) - 1], Cn[abs(tc->lit1) - 1]);
        }

        if (tc->lit2 != 0){ 
            if (tc->lit2 > 0)
                Cp[tc->lit2 - 1]++;
            else 
                Cn[-tc->lit2 - 1]++;
            J[abs(tc->lit2) - 1] += powf(2.0f, -(float)clauselen);
            CpPCn[abs(tc->lit2) - 1]++;
            CpMCn[abs(tc->lit2) - 1] = MAX(Cp[abs(tc->lit2) - 1], Cn[abs(tc->lit2) - 1]);
        }

        if (tc->lit3 != 0){ 
            if (tc->lit3 > 0)
                Cp[tc->lit3 - 1]++;
            else 
                Cn[-tc->lit3 - 1]++;
            J[abs(tc->lit3) - 1] += powf(2.0f, -(float)clauselen);
            CpPCn[abs(tc->lit3) - 1]++;
            CpMCn[abs(tc->lit3) - 1] = MAX(Cp[abs(tc->lit3) - 1], Cn[abs(tc->lit3) - 1]);
        }
        numberofclause++;
        tc = tc->next;
    }
    uint32_t ret = 0;
    uint32_t score = 0;
    float fscore = 0.0f;
    switch (heuristicmode)
    {
    case HEUR_RANDOM:{
        clause_list tcl = cl;
        uint32_t bound = rand() % numberofclause;
        for (uint32_t i = 0; i < bound; i++)
            tcl = tcl->next;
        
        return chooseLit_FIRST(tcl);
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
        return ret + 1;
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
        return ret + 1;
        break;
    }

    case HEUR_JW:{
        for (uint32_t i = 0; i < vsize; i++)
        {
            if (fscore < J[i]){
                ret = i;
                fscore = J[i];
            }
        }
        return ret + 1;
        break;
    }

    default:
        break;
    }
    return chooseLit_FIRST(cl);
}