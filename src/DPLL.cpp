#include "DPLL.h"

DPLL::DPLL(formula f, uint8_t heurmode) : p_formula(f) , p_heurmode(heurmode)
{}

DPLL::~DPLL()
{}

bool DPLL::recDPLL(ClauseList* f){  
    if (!f->unit_propagate(p_formula.p_valuations))
        return false;
        
    if (f->p_CL->empty())
        return true;

    literal l = Heuristic::chooseLit(f->p_CL, p_formula.p_nbVars, p_heurmode);
    ClauseList* fp = f->copy();
    bool tret = false;

    p_formula.p_valuations[l-1] = TRUE;
    fp->naiveval(l);

    if (recDPLL(fp)){
        delete fp;
        return true;
    }
    else{ // in this cas we only tested for l "positive" so we need to look for "negative" aswell OPTI TODO: make a function that checks if either is available 
        p_formula.p_valuations[l-1] = FALSE;
        delete fp;
        fp = f->copy();
        if (fp->eval(-l))
            tret = recDPLL(fp);
        delete fp;
        return tret;
    } 
    
}
bool DPLL::run(){
    ClauseList* operating = new ClauseList();
    operating->p_CL = new std::vector<std::vector<literal>>(*p_formula.p_clauses.p_CL);
    bool ret = recDPLL(operating);
    delete operating;
    if (!ret)
        valuation::flushValuations(p_formula.p_valuations, p_formula.p_nbVars);
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
JWpre -> |  8.9 |  9.8 |  11.8 |  20.4 |  59.4 | 169.0 | 703.7 |   -   |
JW without preproc :
[+] serie of 20 variables had average time 7.121 ms
[+] serie of 50 variables had average time 7.561 ms
[+] serie of 75 variables had average time 10.54 ms
[+] serie of 100 variables had average time 23.217 ms
[+] serie of 125 variables had average time 82.45 ms
[+] serie of 150 variables had average time 274.9 ms

JW with preproc :
[+] serie of 20 variables had average time 6.733 ms
[+] serie of 50 variables had average time 7.727 ms
[+] serie of 75 variables had average time 10.71 ms
[+] serie of 100 variables had average time 23.257 ms
[+] serie of 125 variables had average time 82.33 ms
[+] serie of 150 variables had average time 273.83 ms

*/