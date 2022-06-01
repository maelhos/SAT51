#pragma once
#include "stdinc.h"
#include "clause.h"
#include <assert.h>

class formula
{
public:
    formula();
    ~formula();

    valuation* p_valuations; // list of stored valuations
    ClauseList p_clauses; // list of the clauses
    uint32_t p_nbClauses; // total number of clauses after loading the CNF
    uint32_t p_nbVars; // total number of variables

    void initFormula(uint32_t nbOfClauses, uint32_t nbOfVariables); // initiate an empty formula with specifics
    void pushClause(std::vector<literal> lits); // push a clause if possible and return true else return false
    void print_formula(); // duh
    formula* copy(); // algorithm always run on a copy
};