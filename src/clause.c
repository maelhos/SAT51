#include "clause.h"

clause_list copyClauses(clause_list cl){
    clause_list retc = 0;
    clause_list tmp = cl;


    while (tmp != 0){
        push(&retc, tmp->lit1, tmp->lit2, tmp->lit3);
        tmp = tmp->next;
    }
    return retc;
}

void push(clause_list* cl, literal l1, literal l2, literal l3){
    clause_list ret = (clause_list)malloc(sizeof(struct _clause_list));
    
    if (*cl == 0){
        ret->next = 0;
        ret->previous = 0;
    }
    else{
        ret->next = *cl;
        ret->previous = 0;
        (*cl)->previous = ret;
    }
    ret->lit1 = l1;
    ret->lit2 = l2;
    ret->lit3 = l3;

    *cl = ret;
}

clause_list pop(clause_list l, clause_list* hd){
    clause_list ret;
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
        }
    else{
        l->next->previous = l->previous;
        if (l->previous != 0){ // normal case in the middle
            l->previous->next = l->next;
            ret = l->previous;
        }
        else{ // head with non empty tail
            l->next->previous = 0;
            ret = l->next;
            *hd = (*hd)->next;
        }
    }
    free(l);
    return ret;
}

void clause_clear(clause_list cl){
    if (cl == 0)
        return;
    else{
        clause_clear(cl->next);
        free(cl);
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
        printf("(");
        print_literal(cl->lit1);
        printf(" || ");
        print_literal(cl->lit2);
        printf(" || ");
        print_literal(cl->lit3);
        printf(")");
        cl = cl->next;
    };
    printf("\n");
}

bool evalCheck(clause_list* cl, literal l){ // just checks if eval(cl, l) woule be sucessfull

    clause_list tc = *cl;

    while (tc != 0)
    {
        if (tc->lit1 == -l){ // not-literal
            if (tc->lit2 == 0 && tc->lit3 == 0)
                return false;
        }
        else if (tc->lit2 == -l){
            if (tc->lit1 == 0 && tc->lit3 == 0)
                return false;
        }
        else if (tc->lit3 == -l){
            if (tc->lit1 == 0 && tc->lit2 == 0)
                return false;
        }
        tc = tc->next;
    }
    return true;
}

bool eval(clause_list* cl, literal l){ // actually modifies and eval

    clause_list tc = *cl;

    while (tc != 0)
    {
        if (tc->lit1 == -l){ // not-literal
            tc->lit1 = 0;
            if (tc->lit2 == 0 && tc->lit3 == 0) // lazy eval for dpll
                return false;
        }
        else if (tc->lit2 == -l){
            tc->lit2 = 0;
            if (tc->lit1 == 0 && tc->lit3 == 0) // lazy eval for dpll
                return false;
        }
        else if (tc->lit3 == -l){
            tc->lit3 = 0;
            if (tc->lit1 == 0 && tc->lit2 == 0) // lazy eval for dpll
                return false;
        }
        else if (tc->lit1 == l || tc->lit2 == l || tc->lit3 == l){ // actual literal
            tc = pop(tc, cl);
            continue;
        }
        
        tc = tc->next;
    }
    return true;
}

bool beval(clause_list* cl, literal l, bool b){ // just to make debgging simpler but lower perf
    if (b)
        return eval(cl, l);
    else
        return eval(cl, -l);
}

bool unit_propagate(clause_list* cl, valuation* v){
    clause_list tc = *cl;

    literal toprog = 0;
    while (tc != 0)
    {
        if (tc->lit1 == 0 && tc->lit2 == 0){
            toprog = tc->lit3;
            break;
        }
        else if (tc->lit1 == 0 && tc->lit3 == 0){
            toprog = tc->lit2;
            break;
        }
        else if (tc->lit3 == 0 && tc->lit2 == 0){
            toprog = tc->lit1;
            break;
        }
        tc = tc->next;
    }

    if (toprog != 0){
        if (evalCheck(cl, toprog)){

            eval(cl, toprog);
            v[abs(toprog)-1] = toprog > 0 ? TRUE : FALSE;
            return unit_propagate(cl, v);

        }
        else
            return false;
    }
    return true;
}

