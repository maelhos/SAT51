#pragma once
#include "stdinc.h"
#include "formula.h"
#include "watchedHeuristic.h"

class watchedDPLL
{
private:
    watchedHeuristic* heur;    
    watchedformula p_wformula;
    uint8_t p_heurmode;
    std::vector<partialFrame>* stack;

    void retrieveStack();
    bool recDPLL();
public:
    watchedDPLL(watchedformula& f, uint8_t heurmode);
    bool run();
    ~watchedDPLL();
};
