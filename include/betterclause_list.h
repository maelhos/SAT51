#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"

struct _literal_list {
    literal lit;
    uint32_t length;
    struct _literal_list* next;
    struct _literal_list* previous;
};
typedef struct _literal_list* literal_list;
void pushll(literal_list* cl, literal l);
literal_list popll(literal_list l, literal_list* hd);


struct _better_clause_list{
    uint32_t headIndex;
    uint32_t tailIndex;
    literal_list literals;
    struct _better_clause_list* next;
    struct _better_clause_list* previous;
};
typedef struct _better_clause_list* better_clause_list;
void pushbl(better_clause_list* cl, literal_list ll);
better_clause_list popbl(better_clause_list l, better_clause_list* hd);
