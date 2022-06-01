#pragma once
#include "stdinc.h"
#include "formula.h"

class quine
{
private:
    formula p_formula;
    uint8_t p_heurmode;

    bool recquine(ClauseList* f, literal l);
public:
    quine(formula f, uint8_t heurmode);
    bool run();
    ~quine();
};