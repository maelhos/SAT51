#include "stdinc.h"
#include "valuation.h"
#include "formula.h"
#include "watchedClause.h"

enum {
    PF_CHOICE,
    PF_PROPAG
};

class partialFrame
{
private:
    uint32_t lit;
    uint8_t oldval;
    uint8_t newval;
public:
    uint8_t type;
    partialFrame(uint32_t l, uint8_t o, uint8_t n, uint8_t t);
    void collapse(uint8_t* state);
    ~partialFrame();
};


class watchedformula
{
private:
    uint32_t nbClauses;
    std::vector<watchedClause>* posWatched;
    std::vector<watchedClause>* negWatched;
public:
    uint8_t* state;
    uint32_t nbVars;
    uint8_t val(uint32_t index);
    watchedformula(formula& f);
    void print();
    ~watchedformula();
    bool eval(int lit, std::vector<partialFrame>* stack, uint8_t type);
    int32_t findBasicUnit();
};
