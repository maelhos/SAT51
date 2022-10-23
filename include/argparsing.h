#pragma once
#include "stdinc.h"
#include "formula.h"
#include "watchedHeuristic.h"

enum {
    ALGO_NONE,
    ALGO_QUINE,
    ALGO_DPLL,
    ALGO_CDCL
};

struct _arg_state {
    char* filename;
    uint8_t algo;
    uint8_t heur;
    bool isCustomSeed;
    uint32_t seed;
    uint8_t threads;
    bool noWatchedLiterals; // unused for now
};
typedef struct _arg_state* arg_state;

void parseargs(int argc, char** argv, arg_state* rs);