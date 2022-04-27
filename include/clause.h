#pragma once
#include "stdinc.h"
#include "literal.h"
#include "valuation.h"

struct _clause_list // we use cyclic double chained list for better perf (cf td 16...) 
{
    struct _clause_list* previous;
    struct _clause_list* next;
    literal lit1;
    literal lit2;
    literal lit3;
};

typedef struct _clause_list* clause_list;

clause_list initClauseList();
clause_list push(clause_list cl, literal l1, literal l2, literal l3);
clause_list copyClauses(clause_list cl);
void pop(clause_list* cl);
bool eval(clause_list* cl, literal l, bool b);