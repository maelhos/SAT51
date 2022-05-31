#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include "better_clause.h"

bool pe(literal a, valuation v);
bool better_eval(better_formula f, literal l, valuation val, bool choiceType, partial_valuation_stack* PVS);