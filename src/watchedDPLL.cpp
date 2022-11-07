#include "watchedDPLL.h"

watchedDPLL::watchedDPLL(watchedformula& f, uint8_t heurmode)
 : p_wformula(f), p_heurmode(heurmode)
{
    heur = new watchedHeuristic(f);
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
    printStack(stack);
    v_printValAsCNF(p_wformula.state, p_wformula.nbVars);
    //p_wformula.print();
    if(stack->size() == p_wformula.nbVars + 1) 
        return true;

    literal l = heur->chooseLit(p_heurmode);

    if (!p_wformula.eval(l, stack, PF_CHOICE)){
        retrieveStack();
        l *= -1;
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
        if (!p_wformula.eval(-l, stack, PF_CHOICE))
            return false;
        if (recDPLL())
            return true;
        else
            return false;
    }

}

bool watchedDPLL::run(){
    
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