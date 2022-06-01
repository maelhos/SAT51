#include "heuristic.h"

literal Heuristic::chooseLit(std::vector<std::vector<literal>>* cl, uint32_t vsize, uint8_t heuristicmode){
    switch (heuristicmode)
    {
    case HEUR_NONE:
        exit(EXIT_SUCCESS);
        break;
    case HEUR_FIRST:
        return chooseLit_FIRST(*cl, vsize);
        break;
    case HEUR_RANDOM:
        return chooseLit_RANDOM(*cl, vsize);
        break;
    case HEUR_JW:
        return chooseLit_JW(*cl, vsize);
        break;
    case HEUR_CS:
        return chooseLit_CS(*cl, vsize);
        break;
    case HEUR_IS:
        return chooseLit_IS(*cl, vsize);
        break;
    default:
        return chooseLit_RANDOM(*cl, vsize);
        break;
    }
}

literal Heuristic::chooseLit_FIRST(std::vector<std::vector<literal>>& cl, uint32_t vsize){
    return abs(cl[0][0]);
}

literal Heuristic::chooseLit_RANDOM(std::vector<std::vector<literal>>& cl, uint32_t vsize){
    uint32_t i = rand() % cl.size();
    uint32_t j = rand() % cl[i].size();
        
    return abs(cl[i][j]);
}

literal Heuristic::chooseLit_JW(std::vector<std::vector<literal>>& cl, uint32_t vsize){
    float* J = (float*)alloca(sizeof(float) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++)
        J[i] = 0.0f;

    for (int32_t i = 0; i < cl.size(); i++)
    {
        for (int32_t j = 0; j < cl[i].size(); j++)
            J[abs(cl[i][j]) - 1] += powf(2.0f, -(float)cl[i].size());
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

literal Heuristic::chooseLit_CS(std::vector<std::vector<literal>>& cl, uint32_t vsize){
    uint32_t* CpPCn = (uint32_t*)alloca(sizeof(uint32_t) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++)
        CpPCn[i] = 0;

    for (int32_t i = 0; i < cl.size(); i++)
    {
        for (int32_t j = 0; j < cl[i].size(); j++)
            CpPCn[abs(cl[i][j]) - 1]++;
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

literal Heuristic::chooseLit_IS(std::vector<std::vector<literal>>& cl, uint32_t vsize){
    uint32_t* CpMCn = (uint32_t*)alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* Cp = (uint32_t*)alloca(sizeof(uint32_t) * (vsize + 1));
    uint32_t* Cn = (uint32_t*)alloca(sizeof(uint32_t) * (vsize + 1));
    for (uint32_t i = 0; i < vsize; i++){
        Cp[i] = 0;
        Cn[i] = 0;
        CpMCn[i] = 0;
    }
    for (int32_t i = 0; i < cl.size(); i++)
    {
        for (int32_t j = 0; j < cl[i].size(); j++){
            if (cl[i][j] > 0)
                Cp[cl[i][j] - 1]++;
            else 
                Cn[-cl[i][j] - 1]++;
            CpMCn[abs(cl[i][j]) - 1] = MAX(Cp[abs(cl[i][j]) - 1], Cn[abs(cl[i][j]) - 1]);
        }
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
