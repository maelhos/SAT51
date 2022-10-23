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
    uint32_t nbV;
    std::vector<int> available;

    literal chooseLit_FIRST  ();
    literal chooseLit_RANDOM ();
    literal chooseLit_JW     ();
    literal chooseLit_CS     ();
    literal chooseLit_IS     ();
public:
    watchedHeuristic(watchedformula& wf, uint32_t nbVars);
    ~watchedHeuristic();
    void onChange(int lit, uint8_t oldval, uint8_t newval);
    literal chooseLit(uint8_t heuristicmode);
};
