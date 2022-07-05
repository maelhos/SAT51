#pragma once
#include "stdinc.h"
#include "watchedLiterals.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

enum {
    WHEUR_NONE,
    WHEUR_FIRST,
    WHEUR_RANDOM,
    WHEUR_JW,
    WHEUR_CS,
    WHEUR_IS
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
