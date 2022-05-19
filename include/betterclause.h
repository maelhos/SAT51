#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"

struct _literal_list {
    literal lit;
    struct _literal_list* next;
    struct _literal_list* previous;
};
typedef _literal_list* literal_list;

struct _better_clause_list{
    uint32_t headIndex;
    uint32_t tailIndex;
    literal_list literals;
    struct _better_clause_list* next;
    struct _better_clause_list* previous;
};
typedef _better_clause_list* better_clause_list;

typedef struct {
    valuation val;
    better_clause_list posHeadList;
    better_clause_list negHeadList;
    better_clause_list posTailList;
    better_clause_list negTailList;
} variable;