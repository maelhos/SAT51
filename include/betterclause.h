#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include "betterclause_list.h"

struct _variable {
    valuation val;
    better_clause_list posHeadList;
    better_clause_list negHeadList;
    better_clause_list posTailList;
    better_clause_list negTailList;
};
typedef struct _variable variable;

struct _better_formula {
    variable* negvars;
    variable* pasvars;
    uint32_t nbClauses; 
    uint32_t nbVars;
}
typedef struct _better_formula* better_formula;

better_formula convert(formula f);
