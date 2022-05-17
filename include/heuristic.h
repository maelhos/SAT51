#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define HEUR_FIRST 0
#define HEUR_RANDOM 1
#define HEUR_BOHM 2
#define HEUR_MOMS 3
#define HEUR_JW 4
#define HEUR_VS 5 // not for now ...
#define HEUR_CS 6
#define HEUR_IS 7


literal chooseLit(clause_list cl, uint32_t vsize, uint8_t heuristicmode);
literal chooseLit_FIRST(clause_list cl);
literal chooseLit_RANDOM();