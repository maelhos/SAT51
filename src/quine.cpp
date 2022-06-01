#include "quine.h"

quine::quine(formula f, uint8_t heurmode) : p_formula(f), p_heurmode(heurmode)
{}

bool quine::recquine(ClauseList* f, literal l){ 
    if (l > p_formula.p_nbVars + 1)
        return false;
        
    if (f->p_CL->empty())
        return true;
    
    for (int32_t i = 0; i < f->p_CL->size(); i++)
    {
        if ((*f->p_CL)[i].empty())  
            return false;
    }
    

    ClauseList* fp = f->copy();
    fp->naiveval(l);
    p_formula.p_valuations[l-1] = TRUE;
    if (recquine(fp, l + 1)){
        delete fp;
        return true;
    }
    else{
        p_formula.p_valuations[l-1] = FALSE;
        delete fp;
        fp = f->copy();
        fp->naiveval(-l);
        bool tret = recquine(fp, l+1);
        delete fp;
        return tret;
    }
}

bool quine::run(){
    ClauseList* operating = new ClauseList();
    operating->p_CL = new std::vector<std::vector<literal>>(*p_formula.p_clauses.p_CL);
    bool ret = recquine(operating, 1);
    delete operating;
    if (!ret)
        valuation::flushValuations(p_formula.p_valuations, p_formula.p_nbVars);
    return ret;
}