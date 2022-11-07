#pragma once
#include "stdinc.h"
#include "watchedLiterals.h"

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

class watchedHeuristic
{
private:
    watchedformula& wfp;

    literal chooseLit_FIRST  ();
    literal chooseLit_RANDOM ();
    literal chooseLit_JW     ();
    literal chooseLit_CS     ();
    literal chooseLit_IS     ();
public:
    watchedHeuristic(watchedformula& wf);
    ~watchedHeuristic();
    literal chooseLit(uint8_t heuristicmode);
};
