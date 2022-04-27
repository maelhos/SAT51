#pragma once
#include "stdinc.h"
#include "formula.h"

bool recquine(clause_list* f, valuation* v, literal l);
bool quine(formula f);