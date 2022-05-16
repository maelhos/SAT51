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

void initHeuristicManager(uint8_t mode, clause_list cl, uint32_t vsize){
    clause_list cp = cl;
    heuristicmode = mode;
    if (heuristicmode == HEUR_RANDOM || heuristicmode == HEUR_CS || heuristicmode == HEUR_IS){
        Cp = malloc(sizeof(uint32_t)*(vsize + 1));
        Cn = malloc(sizeof(uint32_t)*(vsize + 1));
        for (uint32_t i = 0; i < vsize; i++){
            Cp[i] = 0;
            Cn[i] = 0;
        }
        
        while (cp != 0){
            if (cp->lit1 > 0)
                Cp[cp->lit1 - 1]++;
            else 
                Cn[-cp->lit1 - 1]++;
            
            if (cp->lit2 > 0)
                Cp[cp->lit2 - 1]++;
            else 
                Cn[-cp->lit2 - 1]++;
            
            if (cp->lit3 > 0)
                Cp[cp->lit3 - 1]++;
            else 
                Cn[-cp->lit3 - 1]++;
            cp = cp->next;
        }
        
        for (uint32_t i = 0; i < vsize; i++){
            CpMCn[i] = MAX(Cp[i], Cn[i]);
            CpPCn[i] = Cp[i] + Cn[i];
        }
    }
    
}