#pragma once
#include "stdinc.h"
#include "formula.h"

bool recquine(clause_list* f, valuation* v, uint32_t vsize, literal l);
bool quine(formula f);
