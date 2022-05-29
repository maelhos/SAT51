#pragma once
#include "stdinc.h"
#include "literal.h"
#include "valuation.h"

struct _literal_list {
    literal lit;
    uint32_t length;
    struct _literal_list* next;
    struct _literal_list* previous;
};
typedef struct _literal_list* literal_list;

literal_list copyll(literal_list cl);
void pushll(literal_list* cl, literal l);
literal_list popll(literal_list l, literal_list* hd);
void print_ll(literal_list ll);
void clearll(literal_list ll);

struct _clause_list // we use double chained list for better perf
{
    struct _clause_list* previous;
    struct _clause_list* next;
    uint32_t length;
    literal_list lits;
};

typedef struct _clause_list* clause_list;

void push(clause_list* cl, literal_list lits);
clause_list copyClauses(clause_list cl);
clause_list pop(clause_list cl, clause_list* hd);
void clause_clear(clause_list cl);

bool evalCheck(clause_list* cl, literal l);
void naiveval(clause_list* cl, literal l);
bool eval(clause_list* cl, literal l);
bool beval(clause_list* cl, literal l, bool b);

bool unit_propagate(clause_list* cl, valuation* v);

void printcl(clause_list cl);
void printcl_sat(clause_list cl);
