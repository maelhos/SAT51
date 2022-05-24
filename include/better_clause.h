#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include "better_clause_list.h"

struct _variable {
    valuation val; // valution of a literal 
    better_clause_list posWatched;
    better_clause_list negWatched;
};
typedef struct _variable variable;

struct _better_formula {
    variable* vars; // array of variables
    uint32_t nbClauses; // total number of clauses after loading the CNF
    uint32_t nbVars; // total number of variables
};
typedef struct _better_formula* better_formula;

enum { PVS_HEURISTIC_CHOICE, PVS_PROPAGATION};
struct _partial_valuation_stack{
    literal lit;
    valuation val;
    uint8_t choiceType;
    uint32_t length;
    struct _partial_valuation_stack* next;
};
typedef struct _partial_valuation_stack* partial_valuation_stack;

void pushPVS(partial_valuation_stack* pvs, literal lit, valuation val, uint8_t choiceType);
void popPVS(partial_valuation_stack* pvs);

better_formula convert(formula f);
void print_better_formula(better_formula f);