#pragma once
#include "stdinc.h"

enum {
    FALSE, TRUE, UNKNOWN
};

class valuation
{
public:
    static valuation* initValuations(uint32_t nbVars); // just init the valutation array
    static void flushValuations(valuation* v, uint32_t nbVars); // flush the valuation to UNKNOWN before (often before running an algorithm)
    static void printValAsCNF(valuation* v, uint32_t nb);
    static valuation* copyValuations(valuation* vp, uint32_t nbVars); // copyyyyyyyyyy paaaaasttee

public:
    valuation(uint8_t val);
    ~valuation();
    uint8_t p_val;
    valuation negate();

    void printValuation(); // duh duh
    char valtochar();
};
