#pragma once
#include "stdinc.h"
#include "formula.h"
#include "heuristic.h"
#include "preprocess.h"

class DPLL
{
private:
    formula p_formula;
    uint8_t p_heurmode;
    
    bool recDPLL(ClauseList* f);
public:
    DPLL(formula f, uint8_t heurmode);
    bool run();
    ~DPLL();
};
