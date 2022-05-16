#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include "heuristic.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize);
bool DPLL(formula f);