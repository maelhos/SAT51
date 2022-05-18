#include "heuristic.h"

literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode){
    switch (heuristicmode)
    {
    case HEUR_FIRST:
        return chooseLit_FIRST(cl, vsize);
        break;
    case HEUR_RANDOM:
        return chooseLit_RANDOM(cl, vsize);
        break;
    case HEUR_JW:
        return chooseLit_JW(cl, vsize);
        break;
    case HEUR_CS:
        return chooseLit_CS(cl, vsize);
        break;
    case HEUR_IS:
        return chooseLit_IS(cl, vsize);
        break;
    default:
        return chooseLit_RANDOM(cl, vsize);
        break;
    }
}

literal chooseLit_FIRST(clause_list cl, uint32_t vsize){
    if (cl->lit1 != 0)
        return abs(cl->lit1);
    else if (cl->lit2 != 0)
        return abs(cl->lit2);
    else if (cl->lit3 != 0)
        return abs(cl->lit3);
    return 0;
}

literal chooseLit_RANDOM(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    uint32_t nbClauses = 0;
    while (tc != 0){
        tc = tc->next;
        nbClauses++;
    }
    tc = cl;
    uint32_t bound = rand() % nbClauses;
    for (uint32_t i = 0; i < bound; i++)
        tc = tc->next;
        
    return chooseLit_FIRST(tc, vsize);
}

literal chooseLit_JW(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    float* J = alloca(sizeof(float) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++)
        J[i] = 0.0f;
    while (tc != 0){
        uint32_t clauselen = NORMALIZE(tc->lit1) + NORMALIZE(tc->lit2) + NORMALIZE(tc->lit3);
        if (tc->lit1 != 0)
            J[abs(tc->lit1) - 1] += powf(2.0f, -(float)clauselen);

        if (tc->lit2 != 0)
            J[abs(tc->lit2) - 1] += powf(2.0f, -(float)clauselen);

        if (tc->lit3 != 0) 
            J[abs(tc->lit3) - 1] += powf(2.0f, -(float)clauselen);
        tc = tc->next;
    }
    float fscore = 0.0f;
    uint32_t ret = 0;
    for (uint32_t i = 0; i < vsize; i++){
        if (fscore < J[i]){
            ret = i;
            fscore = J[i];
        }
    }
    return ret + 1;
}

literal chooseLit_CS(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    uint32_t* CpPCn = alloca(sizeof(uint32_t) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++)
        CpPCn[i] = 0;

    while (tc != 0){
        if (tc->lit1 != 0)
            CpPCn[abs(tc->lit1) - 1]++;
        if (tc->lit2 != 0)
            CpPCn[abs(tc->lit2) - 1]++;
        if (tc->lit3 != 0)
            CpPCn[abs(tc->lit3) - 1]++;
        tc = tc->next;
    }
    uint32_t score = 0;
    uint32_t ret = 0;
    for (uint32_t i = 0; i < vsize; i++){
        if (score < CpPCn[i]){
            ret = i;
            score = CpPCn[i];
        }
    }
    return ret + 1;
}

literal chooseLit_IS(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    uint32_t* CpMCn = alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* Cp = alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* Cn = alloca(sizeof(uint32_t) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++){
        Cp[i] = 0;
        Cn[i] = 0;
        CpMCn[i] = 0;
    }
    while (tc != 0){
        if (tc->lit1 != 0){ 
            if (tc->lit1 > 0)
                Cp[tc->lit1 - 1]++;
            else 
                Cn[-tc->lit1 - 1]++;
            CpMCn[abs(tc->lit1) - 1] = MAX(Cp[abs(tc->lit1) - 1], Cn[abs(tc->lit1) - 1]);
        }

        if (tc->lit2 != 0){ 
            if (tc->lit2 > 0)
                Cp[tc->lit2 - 1]++;
            else 
                Cn[-tc->lit2 - 1]++;
            CpMCn[abs(tc->lit2) - 1] = MAX(Cp[abs(tc->lit2) - 1], Cn[abs(tc->lit2) - 1]);
        }

        if (tc->lit3 != 0){ 
            if (tc->lit3 > 0)
                Cp[tc->lit3 - 1]++;
            else 
                Cn[-tc->lit3 - 1]++;
            CpMCn[abs(tc->lit3) - 1] = MAX(Cp[abs(tc->lit3) - 1], Cn[abs(tc->lit3) - 1]);
        }
        tc = tc->next;
    }
    uint32_t ret = 0;
    uint32_t score = 0;
    for (uint32_t i = 0; i < vsize; i++){
        if (score < CpMCn[i]){
            ret = i;
            score = CpMCn[i];
        }
    }
    return ret + 1;
}
