#pragma once
#include "stdinc.h"
#include "formula.h"
#include "clause.h"

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
static uint8_t heuristicmode = HEUR_FIRST; // default

// BOHM SPECIFIC
static uint32_t* h1;
static uint32_t* h2;
static uint32_t* h3;
static uint32_t* H1;
static uint32_t* H2;
static uint32_t* H3;
static const int32_t alpha = 1;
static const int32_t beta = 1;
// BOHN END

// MOMS SPECIFIC
static const uint32_t k = 10;
static uint32_t* f;
static uint32_t* S;
// MOMS END

// JW SPECIFIC
static uint32_t* J;
// JW END

// RDLCS / RDLIS SPECIFIC

// RDLCS / RDLIS END
static uint32_t* CpPCn; // used for RDLCS
static uint32_t* CpMCn; // used for RDLIS
// JW END

static uint32_t* Cp; // required for RDLCS / RDLIS / RANDOM
static uint32_t* Cn;

void initHeuristicManager(uint8_t mode, clause_list cl, uint32_t vsize);
literal chooseLit_FIRST(clause_list cl);
literal chooseLit_RANDOM();
