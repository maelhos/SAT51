#include "watchedClause.h"


watchedClause::watchedClause(std::vector<int>& li) : lits(li)
{
    if (li.size() == 1)
        watched2_index = 0;
    else
        watched2_index = 1;
    watched1_index = 0;
    watched1 = lits[watched1_index];
    watched2 = lits[watched2_index];
}

watchedClause::~watchedClause()
{
}

uint32_t watchedClause::size(){
    return lits.size();
}

int watchedClause::operator[](uint32_t i){
    return lits[i];
}

void watchedClause::print(){
    std::cout << "(" << watched1_index << "," << watched2_index << ": ";
    for (uint32_t i = 0; i < lits.size(); i++){
        std::cout << lits[i];
        if (i+1 < lits.size())
            std::cout << " ";
    }
    std::cout << ")";
}

int32_t watchedClause::getUnit(uint8_t* state){
    if (watched1_index == watched2_index)
        return watched1;
    if(state[abs(watched1) - 1] == UNKNOWN)
        return watched1;
    else
        return watched2;
}

void watchedClause::move(std::vector<watchedClause>& from, uint32_t origin_index, std::vector<watchedClause>& to){ /// everythin is wrong here
    std::swap(from[origin_index], from.back());
    from.pop_back();
}

uint8_t watchedClause::eval(int lit, uint8_t* state, std::vector<watchedClause>& from, 
                            uint32_t origin_index, std::vector<watchedClause>* pos, std::vector<watchedClause>* neg){
    if (isSAT(watched1, state[abs(watched1) - 1]) || isSAT(watched2, state[abs(watched2) - 1]))
        return WCLAUSE_SAT_OR_UK_NO_MOVE;
    
    uint8_t ret = WCLAUSE_UNSAT;
    uint32_t* wci = lit == watched1 ? &watched1_index : &watched2_index;
    int32_t* wc = lit == watched1 ? &watched1 : &watched2;
    for (uint32_t i = 0; i < lits.size(); i++)
    {
        if (i == watched1_index || i == watched2_index)
            continue;
        if (isSAT(lits[i], state[abs(lits[i]) - 1])){ // segfault goes here cuz lits is broken
            *wci = i;
            *wc = lits[i];
            if (lits[i] > 0)
                move(from, origin_index, pos[lits[i] - 1]);
            else
                move(from, origin_index, neg[-lits[i] - 1]);
            return WCLAUSE_SAT_OR_UK_MOVE;
        }
        if (state[abs(lits[i]) - 1] == UNKNOWN){
            *wci = i;
            *wc = lits[i];
            if (lits[i] > 0)
                move(from, origin_index, pos[lits[i] - 1]);
            else
                move(from, origin_index, neg[-lits[i] - 1]);
            ret = WCLAUSE_SAT_OR_UK_MOVE;
        }    
    }
    if ((state[abs(watched1) - 1] == UNKNOWN || state[abs(watched2) - 1] == UNKNOWN) && ret == WCLAUSE_UNSAT)
        return WCLAUSE_UNIT;
    return ret;
}