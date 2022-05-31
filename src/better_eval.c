#include "better_eval.h"

inline bool pe(literal a, valuation v){
    if (v == UNKNOWN)
        return false;
    return (a > 0) ? (v == TRUE) : (v == FALSE);
}

bool better_eval(better_formula f, literal l, valuation val, bool choiceType, partial_valuation_stack* PVS){
    pushPVS(PVS, l, (f->vars + l - 1)->val, val, choiceType); // push affectation to the stack
    (f->vars + l - 1)->val = val; // affect partial valuation
    
    if (val == TRUE){
        better_clause_list wn = (f->vars + l - 1)->negWatched;
        while (wn != 0){
            literal_list tl = wn->literals; // pointer to the literal list
            if (pe(wn->watched1, (f->vars + abs(wn->watched1) - 1)->val) || 
            pe(wn->watched2, (f->vars + abs(wn->watched2) - 1)->val))
                goto SatClause; // if there is a correct watched literal... we fine
            
            uint32_t i = 0;
            while (tl != 0){
                if (pe(tl->lit, (f->vars + abs(tl->lit) - 1)->val)){ // found a valid candidate
                    if (wn->watched1 == -l){ // is first watched
                        wn->watched1 = tl->lit;
                        wn->watched_1_index = i;
                    }
                    else{ // is seconde one
                        wn->watched2 = tl->lit;
                        wn->watched_2_index = i;
                    }
                    if (tl->lit > 0){
                        wn = popbl_nofree(wn, &(f->vars + l - 1)->negWatched);
                        wn->next = (f->vars + tl->lit - 1)->posWatched;
                        wn->previous = 0;
                        (f->vars + tl->lit - 1)->posWatched = wn;
                    }
                    else {
                        wn = popbl_nofree(wn, &(f->vars - l - 1)->posWatched);
                        wn->next = (f->vars - tl->lit - 1)->negWatched;
                        wn->previous = 0;
                        (f->vars - tl->lit - 1)->negWatched = wn;
                    }
                    goto PopClause;
                }

                tl = tl->next;
                i++;
            }
            

            
            
            SatClause:;
            wn = wn->next;
            PopClause:;
        }
    }
    return true;
}