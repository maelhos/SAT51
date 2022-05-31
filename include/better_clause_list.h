#pragma once
#include "stdinc.h"
#include "formula.h"


struct _better_clause_list{
    uint32_t watched_1_index;
    uint32_t watched_2_index;
    literal watched1;
    literal watched2;
    literal_list literals;
    struct _better_clause_list* next;
    struct _better_clause_list* previous;
};
typedef struct _better_clause_list* better_clause_list;

void pushbl(better_clause_list* cl, literal_list ll);
better_clause_list popbl(better_clause_list l, better_clause_list* hd);
better_clause_list popbl_nofree(better_clause_list l, better_clause_list* hd);
void print_bl(better_clause_list ll);