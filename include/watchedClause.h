#include "stdinc.h"
#include "valuation.h"
#include "formula.h"

enum{
    WCLAUSE_UNSAT,
    WCLAUSE_SAT_OR_UK_NO_MOVE,
    WCLAUSE_SAT_OR_UK_MOVE,
    WCLAUSE_UNIT
};

inline bool isSAT(literal l, uint8_t v){
    if (v == UNKNOWN)
        return 0;
    if (l > 0)
        return v;
    else
        return !v;
}

class watchedClause
{
private:
    std::vector<int> lits;
    uint32_t watched1_index;
    uint32_t watched2_index;
    int32_t watched1;
    int32_t watched2;
public:
    uint32_t size();
    int operator[](uint32_t i);
    uint8_t eval(int lit, uint8_t* state, std::vector<watchedClause>& from, uint32_t origin_index, std::vector<watchedClause>* pos, std::vector<watchedClause>* neg);
    void move(std::vector<watchedClause>& from, uint32_t origin_index, std::vector<watchedClause>& to);
    int32_t getUnit(uint8_t* state);
    void print();
    watchedClause(std::vector<int>& li);
    ~watchedClause();
};
