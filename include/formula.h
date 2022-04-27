#pragma once
#include "valuation.h"
#include "stdinc.h"
#include "clause.h"
#include <assert.h>

struct _formula
{
    valuation* valuations; // list of stored valuations
    clause_list clauses; // list of the clauses
    uint32_t nbClauses; // total number of clauses after loading the CNF
    uint32_t nbVars; // total number of variables
};
typedef struct _formula* formula;

formula initFormula(uint32_t nbOfClauses, uint32_t nbOfVariables); // initiate an empty formula with specifics
void pushClause(formula f, literal l1, literal l2, literal l3); // push a clause if possible and return true else return false
void print_formula(formula f); // duh
formula copy(formula f); // algorithm always run on a copy