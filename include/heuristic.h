#pragma once
#include "stdinc.h"
#include "formula.h"
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

class Heuristic

{
private:
    static literal chooseLit_FIRST(std::vector<std::vector<literal>>& cl, uint32_t vsize);
    static literal chooseLit_RANDOM(std::vector<std::vector<literal>>& cl, uint32_t vsize);
    static literal chooseLit_JW(std::vector<std::vector<literal>>& cl, uint32_t vsize);
    static literal chooseLit_CS(std::vector<std::vector<literal>>& cl, uint32_t vsize);
    static literal chooseLit_IS(std::vector<std::vector<literal>>& cl, uint32_t vsize);
public:
    static literal chooseLit(std::vector<std::vector<literal>>* cl, uint32_t vsize, uint8_t heuristicmode);
};
