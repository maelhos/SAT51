#include "watchedHeuristic.h"

watchedHeuristic::watchedHeuristic(watchedformula& wf, uint32_t nbVars) :  nbV(nbVars) {
    available.reserve(nbVars + 1);

    for (uint32_t i = 0; i < nbVars; i++)
        available[i] = wf.val(i) == UNKNOWN; 
    
}

watchedHeuristic::~watchedHeuristic(){}

void watchedHeuristic::onChange(int lit, uint8_t oldval, uint8_t newval){
    if (oldval == UNKNOWN || newval != UNKNOWN)
        available[abs(lit) - 1] = 0;
    if (oldval != UNKNOWN || newval == UNKNOWN)
        available[abs(lit) - 1] = 1;
}

literal watchedHeuristic::chooseLit(uint8_t heuristicmode){
    switch (heuristicmode)
    {
    case HEUR_NONE:
        exit(EXIT_SUCCESS);
        break;
    case HEUR_FIRST:
        return chooseLit_FIRST();
        break;
    case HEUR_RANDOM:
        return chooseLit_RANDOM();
        break;
    case HEUR_JW:
        return chooseLit_JW();
        break;
    case HEUR_CS:
        return chooseLit_CS();
        break;
    case HEUR_IS:
        return chooseLit_IS();
        break;
    default:
        return chooseLit_RANDOM();
        break;
    }
}

literal watchedHeuristic::chooseLit_FIRST(){
    for (uint32_t i = 0; i < nbV; i++)
    {
        if (available[i])
            return i + 1;
    }
    return 0;
}

literal watchedHeuristic::chooseLit_RANDOM(){
    while (true)
    {
        int rd = rand() % nbV;
        if (available[rd])
            return rd + 1;
    }
}

literal watchedHeuristic::chooseLit_JW(){
    return 0;
}

literal watchedHeuristic::chooseLit_CS(){
    return 0;
}

literal watchedHeuristic::chooseLit_IS(){
    return 0;
}
