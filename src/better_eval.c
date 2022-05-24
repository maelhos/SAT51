#include "better_eval.h"


bool better_eval(better_formula f, literal l, valuation val, bool choiceType, partial_valuation_stack* PVS){
    (f->vars + l - 1)->val = val; // affect partial valuation
    pushPVS(PVS, l, val, choiceType); // push affectation to the stack
    if (val == TRUE){
        better_clause_list wn = (f->vars + l - 1)->negWatched;
        while (wn != 0){
            literal_list tl = wn->literals; // pointer to the literal list
            uint32_t indexofwatched = l == wn->watched1 ? wn->watched_1_index : wn->watched_2_index; // get index of l
            
            if (wn->watched1 > 0 ? ((f->vars + wn->watched1 - 1)->val == TRUE) : ((f->vars - wn->watched1 - 1)->val == FALSE))
                goto SatClause; // a positive watched literal is found
            while (tl != 0)

            
            
            SatClause:;
            wn = wn->next;
        }
    }
    return true;
}