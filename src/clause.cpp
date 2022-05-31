#include "clause.h"

inline void pushll(literal_list* cl, literal l){
    literal_list ret = (literal_list)malloc(sizeof(struct _literal_list));
    
    if (*cl == 0){
        ret->next = 0;
        ret->previous = 0;
        ret->length = 1;
    }
    else{
        ret->next = *cl;
        ret->previous = 0;
        ret->length = (*cl)->length + 1;
        (*cl)->previous = ret;
    }
    ret->lit = l;
    *cl = ret;
}
inline literal_list popll(literal_list l, literal_list* hd){
    literal_list ret;
    if (l == 0)
        return 0;
    if (l->next == 0)
        if (l->previous == 0){ // only one element7
            *hd = 0;
            ret = 0;
        }
        else{ // ending element
            l->previous->next = 0;
            ret = l->previous;
            (*hd)->length--;
        }
    else{
        l->next->previous = l->previous;
        if (l->previous != 0){ // normal case in the middle
            l->previous->next = l->next;
            ret = l->previous;
            (*hd)->length--;
        }
        else{ // head with non empty tail
            l->next->previous = 0;
            ret = l->next;
            (*hd)->next->length = (*hd)->length - 1;
            *hd = (*hd)->next;
        }
    }
    free(l);
    return ret;
}

void print_ll(literal_list ll){
    literal_list llp = ll;
    printf("(");
    while (llp != 0){
        printf("%d ", llp->lit);
        llp = llp->next;
    }
    printf(")");
}
inline literal_list copyll(literal_list cl){
    literal_list retc = 0;
    literal_list tmp = cl;


    while (tmp != 0){
        pushll(&retc, tmp->lit);
        tmp = tmp->next;
    }
    return retc;
}
inline void clearll(literal_list ll){
    if (ll == 0)
        return;
    else{
        clearll(ll->next);
        free(ll);
    }
}

inline clause_list copyClauses(clause_list cl){
    clause_list retc = 0;
    clause_list tmp = cl;

    while (tmp != 0){
        push(&retc, copyll(tmp->lits));
        tmp = tmp->next;
    }
    retc->length = cl->length;
    return retc;
}

inline void push(clause_list* cl, literal_list lits){
    clause_list ret = (clause_list)malloc(sizeof(struct _clause_list));
    
    if (*cl == 0){ // empty
        ret->next = 0;
        ret->previous = 0;
        ret->length = 1;
    }
    else{
        ret->next = *cl;
        ret->previous = 0;
        ret->length = (*cl)->length + 1;
        (*cl)->previous = ret;
    }
    ret->lits = lits;


    *cl = ret;
}

inline clause_list pop(clause_list l, clause_list* hd){
    clause_list ret;
    if (l == 0)
        return 0;
    if (l->next == 0)
        if (l->previous == 0){ // only one element
            *hd = 0;
            ret = 0;
        }
        else{ // ending element
            l->previous->next = 0;
            (*hd)->length--;
            ret = l->previous;
        }
    else{
        l->next->previous = l->previous;
        if (l->previous != 0){ // normal case in the middle
            l->previous->next = l->next;
            (*hd)->length--;
            ret = l->previous;
        }
        else{ // head with non empty tail
            l->next->previous = 0;
            ret = l->next;
            (*hd)->next->length = (*hd)->length - 1;
            *hd = (*hd)->next;
        }
    }
    clearll(l->lits);
    free(l);
    return ret;
}

inline void clause_clear(clause_list cl){
    if (cl == 0)
        return;
    else{
        clause_clear(cl->next);
        clearll(cl->lits);
    }
}

void printcl(clause_list cl){
    if (cl == 0){
        printf("SAT\n");
        return;
    }
    bool first = true;
    while (cl != 0) {
        if (first)
            first = false;
        else
            printf(" && ");
        print_ll(cl->lits);
        cl = cl->next;
    };
    printf("\n");
}

void printcl_sat(clause_list cl){
    if (cl == 0)
        printf("SAT\n");
    else 
        printf("UNSAT\n");
}

inline bool evalCheck(clause_list* cl, literal l){ // just checks if eval(cl, l) woule be sucessfull

    clause_list tc = *cl;

    while (tc != 0)
    {
        literal_list ll = tc->lits;
        if (ll->length == 1 && ll->lit == -l)
            return false;
        tc = tc->next;
    }
    return true;
}

void naiveval(clause_list* cl, literal l){

    clause_list tc = *cl;

    while (tc != 0)
    {   
        literal_list ll = tc->lits;

        while (ll != 0){
            if (ll->lit == l){
                tc = pop(tc, cl);
                goto Continue;
            }
            else if (ll->lit == -l){
                ll = popll(ll, &tc->lits);
                continue;
            }
            ll = ll->next;
        }
        tc = tc->next;
        Continue:;
    }
}

bool eval(clause_list* cl, literal l){ // actually modifies and eval

    clause_list tc = *cl;

    while (tc != 0)
    {   
        literal_list ll = tc->lits;

        if (ll->length == 1 && ll->lit == -l)
            return false;

        while (ll != 0){
            if (ll->lit == l){
                tc = pop(tc, cl);
                goto Continue;
            }
            else if (ll->lit == -l){
                ll = popll(ll, &tc->lits);
                continue;
            }
            ll = ll->next;
        }
        tc = tc->next;
        Continue:;
    }
    return true;
}

bool beval(clause_list* cl, literal l, bool b){ // just to make debgging simpler but lower perf
    if (b)
        return eval(cl, l);
    else
        return eval(cl, -l);
}

inline bool unit_propagate(clause_list* cl, valuation* v){
    Save_the_stackkkk:;
    clause_list tc = *cl;

    literal topropagate = 0;
    while (tc != 0)
    {
        if (tc->lits->length == 1){
            topropagate = tc->lits->lit;
            break;
        }
        tc = tc->next;
    }
    if (topropagate != 0){
        if (evalCheck(cl, topropagate)){
            eval(cl, topropagate);
            v[abs(topropagate)-1] = topropagate > 0 ? TRUE : FALSE;
            goto Save_the_stackkkk;

        }
        else
            return false;
    }
    return true;
}

