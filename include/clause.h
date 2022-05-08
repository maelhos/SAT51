#pragma once
#include "stdinc.h"
#include "literal.h"
#include "valuation.h"

struct _clause_list // we use double chained list for better perf
{
    struct _clause_list* previous;
    struct _clause_list* next;
    literal lit1;
    literal lit2;
    literal lit3;
};

typedef struct _clause_list* clause_list;

clause_list initClauseList();
void push(clause_list* cl, literal l1, literal l2, literal l3);
clause_list copyClauses(clause_list cl);
clause_list pop(clause_list cl, clause_list* hd);
bool eval(clause_list* cl, literal l, bool b);
void printcl(clause_list cl);