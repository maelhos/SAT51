#include "clause.h"

clause_list initClauseList(){
    return 0;
}

clause_list copyClauses(clause_list cl){
    clause_list retc = initClauseList(); // lol
    clause_list tmp = cl;

    clause_list l_init = tmp;

    do{
        retc = push(retc, tmp->lit1, tmp->lit2, tmp->lit3);
        tmp = tmp->next;
    } while (tmp != l_init);
    return retc;
}

clause_list push(clause_list cl, literal l1, literal l2, literal l3){
    clause_list ret = (clause_list)malloc(sizeof(struct _clause_list));
    
    if (cl == 0){
        ret->next = ret;
        ret->previous = ret;
    }
    else{
        ret->next = cl;
        ret->previous = cl->previous;
        cl->previous->next = ret;
        cl->previous = ret;
    }
    ret->lit1 = l1;
    ret->lit2 = l2;
    ret->lit3 = l3;
    return ret;
}

bool eval(clause_list* cl, literal l, bool b){
    if (*cl == 0)
        return true;

    if (!b)
        l *= -1;

    clause_list tc = *cl;
    uint32_t clauselen = 0;
    do {
        clauselen++;
        tc = tc->next;
    } while (tc != cl);

    for (uint32_t i = 0; i < clauselen; i++)
    {
        if (tc->lit1 == -l){ // not-literal
            if (tc->lit2 == 0 && tc->lit2 == 0) // lazy eval
                return false;
            tc->lit1 = 0;
        }
        else if (tc->lit2 == -l){
            if (tc->lit1 == 0 && tc->lit3 == 0) // lazy eval
                return false;
            tc->lit2 = 0;
        }
        else if (tc->lit3 == -l){
            if (tc->lit1 == 0 && tc->lit2 == 0) // lazy eval
                return false;
            tc->lit3 = 0;
        }
        else if (tc->lit1 == l || tc->lit2 == l || tc->lit3 == l){ // actual literal
            pop(&tc);
            if (tc == 0){
                *cl = 0;
                return true;
            }
        }
        
        tc = tc->next;
    }
    



    
    
}

void pop(clause_list* l){
    clause_list lx = *l;
    if (lx == 0)
        return;
    if (lx->previous == lx || lx->next == lx)
        *l = 0;
    else{
        lx->previous->next = lx->next;
        lx->next->previous = lx->previous;
        *l = lx->next;
        free(lx);
    }
}