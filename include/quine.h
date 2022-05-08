#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"

bool recquine(clause_list* f, valuation* v, uint32_t vsize, literal l, uint64_t cnt);
bool quine(formula f);