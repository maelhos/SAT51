#include "heuristic.h"

inline literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode){
    switch (heuristicmode)
    {
    case HEUR_NONE:
        exit(EXIT_SUCCESS);
        break;
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

inline literal chooseLit_FIRST(clause_list cl, uint32_t vsize){
    return abs(cl->lits->lit);
}

inline literal chooseLit_RANDOM(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    uint32_t bound = rand() % cl->length;
    for (uint32_t i = 0; i < bound; i++)
        tc = tc->next;
        
    return chooseLit_FIRST(tc, vsize);
}

inline literal chooseLit_JW(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    float* J = alloca(sizeof(float) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++)
        J[i] = 0.0f;
    while (tc != 0){
        uint32_t clauselen = tc->lits->length;
        literal_list tll = tc->lits;

        while (tll != 0){
            J[abs(tll->lit) - 1] += powf(2.0f, -(float)clauselen);
            tll = tll->next;
        }
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

inline literal chooseLit_CS(clause_list cl, uint32_t vsize){
    clause_list tc = cl;
    uint32_t* CpPCn = alloca(sizeof(uint32_t) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++)
        CpPCn[i] = 0;

    while (tc != 0){
        literal_list tll = tc->lits;

        while (tll != 0){
            CpPCn[abs(tll->lit) - 1] ++;
            tll = tll->next;
        }
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

inline literal chooseLit_IS(clause_list cl, uint32_t vsize){
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
        literal_list tll = tc->lits;

        while (tll != 0){
            if (tll->lit > 0)
                Cp[tll->lit - 1]++;
            else 
                Cn[-tll->lit - 1]++;
            CpMCn[abs(tll->lit) - 1] = MAX(Cp[abs(tll->lit) - 1], Cn[abs(tll->lit) - 1]);

            tll = tll->next;
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
