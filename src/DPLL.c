#include "DPLL.h"

bool recDPLL(clause_list* f, valuation* v, uint32_t vsize, uint8_t heurmode){  

    if (!unit_propagate(f, v))
        return false;
        
    if (*f == 0)
        return true;

    literal l = chooseLit(*f, vsize, heurmode);
    clause_list fp = copyClauses(*f);
    bool tret = false;

    v[l-1] = TRUE;
    eval(&fp, l);
    if (recDPLL(&fp, v, vsize, heurmode)){
        clause_clear(fp);
        return true;
    }
    else{ // in this cas we only tested for l "positive" so we need to look for "negative" aswell OPTI TODO: make a function that checks if either is available 
        v[l-1] = FALSE;
        clause_clear(fp);
        fp = copyClauses(*f);
        if (eval(&fp, -l))
            tret = recDPLL(&fp, v, vsize, heurmode);
        clause_clear(fp);
        return tret;
    } 
    
}
bool DPLL(formula f){
    //clause_list operating = copyClauses(f->clauses);
    clause_list operating = preprocess(f->clauses);
    bool ret = recDPLL(&operating, f->valuations, f->nbVars, HEUR_JW);
    clause_clear(operating);
    if (!ret)
        flushValuations(f->valuations, f->nbVars);
    return ret;
}

/*
timeout = 5s
time in ms
x = no sucess at all
- = some success but still some outime
         | uf20 | uf50 | uf75  | uf100 | uf125 | uf150 | uf175 | uf200 |
QUINE -> | 13.7 |  x   |   x   |   x   |   x   |   x   |   x   |   x   | y
FIRST -> |  9.5 | 12.2 |  44.1 | 367.6 |   -   |   x   |   x   |   x   | y
RDLIS -> |  8.9 | 10.3 |  21.4 |  93.4 | 564.9 |   -   |   x   |   x   | y
RDLCS -> |  8.7 | 11.2 |  16.4 |  49.6 | 309.7 |   -   |   x   |   x   | y 
JW    -> |  8.5 |  9.4 |  12.3 |  25.1 |  83.6 | 287.4 |   -   |   x   | y

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