#pragma once
#include "valuation.h"
#include "stdinc.h"
#include "clause.h"

struct _formula
{
    valuation* valuations;
    clause_list clauses;
    uint16_t nbClauses;
    uint16_t nbVars;
};
typedef struct _formula* formula;

formula initFormula(uint16_t nbOfClauses, uint16_t nbOfVariables);