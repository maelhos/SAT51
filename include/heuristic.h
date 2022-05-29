#pragma once
#include "stdinc.h"
#include "formula.h"
#include "literal.h"
#include "clause.h"
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

enum {
    HEUR_NONE,
    HEUR_FIRST,
    HEUR_RANDOM,
    HEUR_JW,
    HEUR_CS,
    HEUR_IS
};


literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode);

literal chooseLit_FIRST(clause_list cl, uint32_t vsize);
literal chooseLit_RANDOM(clause_list cl, uint32_t vsize);
literal chooseLit_JW(clause_list cl, uint32_t vsize);
literal chooseLit_CS(clause_list cl, uint32_t vsize);
literal chooseLit_IS(clause_list cl, uint32_t vsize);