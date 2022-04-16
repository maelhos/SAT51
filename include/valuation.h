#pragma once
#include "stdinc.h"

typedef enum {
    FALSE = 0, TRUE = 1, UNKNOWN = 2
} valuation;

valuation* initValuations(uint16_t nbVars);
void printValuation(valuation v);