#include "clause.h"

ClauseList::ClauseList(){
    p_CL = new std::vector<std::vector<literal>>;
}

ClauseList::~ClauseList()
{}


void ClauseList::printcl(){
    if (p_CL->empty()){
        std::cout << "SAT" << std::endl;
        return;
    }
    bool first = true;
    for (size_t i = 0; i < p_CL->size(); i++)
    {
        std::cout << "(";
        for (size_t j = 0; j < (*p_CL)[i].size(); j++)
            std::cout << (*p_CL)[i][j] << " ";
        std::cout << ") &&";
    }
    std::cout << std::endl;
}

void ClauseList::printcl_sat(){
    if (p_CL->empty())
        std::cout << "SAT" << std::endl;
    else 
        std::cout << "UNSAT" << std::endl;
}

inline bool ClauseList::evalCheck(literal l){ // just checks if eval(cl, l) woule be sucessfull

    for (int32_t i = 0; i < p_CL->size(); i++)
    {
        if ((*p_CL)[i].size() == 1 && (*p_CL)[i][0] == -l)
            return false;
    }
    return true;
}

void ClauseList::naiveval(literal l){

    for (int32_t i = 0; i < p_CL->size(); i++)
    {
        for (int32_t j = 0; j < (*p_CL)[i].size(); j++)
        {
            if ((*p_CL)[i][j] == l){
                p_CL->erase(p_CL->begin() + i);
                i--;
                break; // not sure here... index pb
            }
            else if ((*p_CL)[i][j] == -l){
                (*p_CL)[i].erase((*p_CL)[i].begin() + j);
                j--;
                continue; // not sure here... index pb
            }
        }
        
    }
}

bool ClauseList::eval(literal l){ // actually modifies and eval

    for (int32_t i = 0; i < p_CL->size(); i++)
    {
        if ((*p_CL)[i].size() == 1 && (*p_CL)[i][0] == -l)
            return false;

        for (int32_t j = 0; j < (*p_CL)[i].size(); j++)
        {
            if ((*p_CL)[i][j] == l){
                p_CL->erase(p_CL->begin() + i);
                i--;
                break; // not sure here... index pb
            }
            else if ((*p_CL)[i][j] == -l){
                (*p_CL)[i].erase((*p_CL)[i].begin() + j);
                j--;
                continue; // not sure here... index pb
            }
        }
    }
    return true;
}

bool ClauseList::beval(literal l, bool b){ // just to make debgging simpler but lower perf
    if (b)
        return eval(l);
    else
        return eval(-l);
}

bool ClauseList::unit_propagate(valuation* v){
    Save_the_stackkkk:;
    literal topropagate = 0;

    for (int32_t i = 0; i < p_CL->size(); i++)
    {
        if ((*p_CL)[i].size() == 1){
            topropagate = (*p_CL)[i][0];
        }
    }
    if (topropagate != 0){
        if (evalCheck(topropagate)){
            naiveval(topropagate);
            v[abs(topropagate)-1] = topropagate > 0 ? TRUE : FALSE;
            goto Save_the_stackkkk;
        }
        else
            return false;
    }
    return true;
}

ClauseList* ClauseList::copy(){
    std::vector<std::vector<literal>>* ret = new std::vector<std::vector<literal>>(*p_CL);

    ClauseList* rc = new ClauseList();
    rc->p_CL = ret;
    return rc;
}
