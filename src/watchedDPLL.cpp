#include "watchedDPLL.h"

watchedDPLL::watchedDPLL(watchedformula& f, uint8_t heurmode)
 : p_wformula(f), p_heurmode(heurmode)
{
    heur = new watchedHeuristic(f, f.nbVars);
    stack = new std::vector<partialFrame>;
    stack->reserve(1); // test
}

watchedDPLL::~watchedDPLL()
{}

void watchedDPLL::retrieveStack(){
    while (true)
    {
        if (stack->size() == 0)
            break;
        if (stack->back().type == PF_CHOICE) {
            stack->back().collapse(p_wformula.state);
            stack->pop_back();
            break;
        }
        stack->back().collapse(p_wformula.state);
        stack->pop_back();
    }
}

bool watchedDPLL::recDPLL(){  
    if(stack->size() == p_wformula.nbVars) 
        return true;

    literal l = heur->chooseLit(p_heurmode);

    heur->onChange(l, p_wformula.state[l - 1], TRUE);
    if (!p_wformula.eval(l, stack, PF_CHOICE)){
        retrieveStack();
        l *= -1;
        heur->onChange(l, p_wformula.state[l - 1], FALSE);
        if (!p_wformula.eval(-l, stack, PF_CHOICE))
            return false;
        if (recDPLL())
            return true;
        else
            return false;
    }

    if (recDPLL())
        return true;
    else{
        retrieveStack();
        l *= -1;
        heur->onChange(l, p_wformula.state[l - 1], FALSE);
        if (!p_wformula.eval(-l, stack, PF_CHOICE))
            return false;
        if (recDPLL())
            return true;
        else
            return false;
    }

}

bool watchedDPLL::run(){
    // pre process to remove original unit clauses.
    int32_t fclause = 0;
    while (true){
        fclause = p_wformula.findBasicUnit();
        if (fclause){
            heur->onChange(abs(fclause), p_wformula.state[abs(fclause) - 1], fclause > 0 ? TRUE : FALSE);
            if (!p_wformula.eval(fclause, stack, PF_CHOICE))
                return false;
        }
        else
            break;
    }
    
    bool ret = recDPLL();
    return ret;
}

/*
timeout = 5s
time in ms
x = no sucess at all
- = some success but still some outime
         | uf20 | uf50 | uf75  | uf100 | uf125 | uf150 | uf175 | uf200 |
QUINE -> | 13.7 |  x   |   x   |   x   |   x   |   x   |   x   |   x   |
FIRST -> |  9.5 | 12.2 |  44.1 | 367.6 |   -   |   x   |   x   |   x   |
RDLIS -> |  8.9 | 10.3 |  21.4 |  93.4 | 564.9 |   -   |   x   |   x   |
RDLCS -> |  8.7 | 11.2 |  16.4 |  49.6 | 309.7 |   -   |   x   |   x   | 
JW    -> |  8.9 |  9.8 |  11.8 |  20.4 |  59.4 | 169.0 | 703.7 |   -   |
*/