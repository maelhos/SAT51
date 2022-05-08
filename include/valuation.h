#pragma once
#include "stdinc.h"

typedef enum {
    FALSE = 0, TRUE = 1, UNKNOWN = 2
} valuation;

valuation* initValuations(uint32_t nbVars); // just init the valutation array
void flushValuations(valuation* v, uint32_t nbVars); // flush the valuation to UNKNOWN before (often before running an algorithm)
void printValuation(valuation v); // duh duh
void printValAsCNF(valuation* v, uint32_t nb);
valuation* copyValuations(valuation* vp, uint32_t nbVars); // copyyyyyyyyyy paaaaasttee