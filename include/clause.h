#pragma once
#include "stdinc.h"
#include "literal.h"
#include "valuation.h"

class ClauseList
{
public:
    std::vector<std::vector<literal>>* p_CL;

    ClauseList();
    ~ClauseList();
    bool evalCheck(literal l);
    void naiveval(literal l);
    bool eval(literal l);
    bool beval(literal l, bool b);

    bool unit_propagate(valuation* v);

    void printcl();
    void printcl_sat();

    ClauseList* copy();
};


