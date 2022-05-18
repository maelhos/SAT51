#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define NORMALIZE(X) ((X) != (0) ? (1) : (0))

#define HEUR_FIRST 0
#define HEUR_RANDOM 1
#define HEUR_JW 2
#define HEUR_CS 3
#define HEUR_IS 4


literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode);

literal chooseLit_FIRST(clause_list cl, uint32_t vsize);
literal chooseLit_RANDOM(clause_list cl, uint32_t vsize);
literal chooseLit_JW(clause_list cl, uint32_t vsize);
literal chooseLit_CS(clause_list cl, uint32_t vsize);
literal chooseLit_IS(clause_list cl, uint32_t vsize);