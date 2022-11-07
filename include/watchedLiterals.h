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
    valuation oldval;
    valuation newval;
public:
    uint8_t type;
    partialFrame(uint32_t l, valuation o, valuation n, uint8_t t);
    void collapse(uint8_t* state);
    void prints();
    ~partialFrame();
};
void printStack(std::vector<partialFrame>* stack);

class watchedformula
{
private:
    uint32_t nbClauses;
    std::vector<watchedClause>* posWatched;
    std::vector<watchedClause>* negWatched;
public:
    valuation* state;
    uint32_t nbVars;

    uint8_t val(uint32_t index);
    watchedformula(formula& f);
    void print();
    ~watchedformula();
    bool eval(int lit, std::vector<partialFrame>* stack, uint8_t type);
};
