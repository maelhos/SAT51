#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include "betterclause_list.h"

struct _variable {
    valuation val; // valution of a literal
    better_clause_list posHeadList; //  
    better_clause_list negHeadList;
    better_clause_list posTailList;
    better_clause_list negTailList;
};
typedef struct _variable variable;

struct _better_formula {
    variable* vars; // array of variables
    uint32_t nbClauses; // total number of clauses after loading the CNF
    uint32_t nbVars; // total number of variables
};
typedef struct _better_formula* better_formula;

better_formula convert(formula f);
void print_better_formula(better_formula f);