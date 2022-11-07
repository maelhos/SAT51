#pragma once
#include "stdinc.h"

enum {
    FALSE, TRUE, UNKNOWN
};
typedef uint8_t valuation;


valuation* v_initValuations(uint32_t nbVars); // just init the valutation array
void v_flushValuations(valuation* v, uint32_t nbVars); // flush the valuation to UNKNOWN before (often before running an algorithm)
void v_printValAsCNF(valuation* v, uint32_t nb);
valuation* v_copyValuations(valuation* vp, uint32_t nbVars); // copyyyyyyyyyy paaaaasttee

valuation v_negate(valuation v);
void v_printValuation(valuation v); // duh duh