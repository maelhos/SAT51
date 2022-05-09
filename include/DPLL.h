#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize, literal l);
bool DPLL(formula f);