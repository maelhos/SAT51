#pragma once
#include "valuation.h"
#include "stdinc.h"
#include "clause.h"

struct _formula
{
    valuation* valuations; // list of stored valuations
    clause_list clauses; // list of the clauses
    uint32_t accClauses; // current nb of clause remaining
    uint32_t nbClauses; // total number of clauses after loading the CNF
    uint32_t nbVars; // total number of variables
};
typedef struct _formula* formula;

formula initFormula(uint32_t nbOfClauses, uint32_t nbOfVariables); // initiate an empty formula with specifics
bool pushClause(formula f, literal l1, literal l2, literal l3); // push a clause if possible and return true else return false
void print_formula(formula f);