#include "clause.h"

clause_list initClauseList(){
    return 0;
}

clause_list copyClauses(clause_list cl){
    clause_list retc = initClauseList(); // lol
    clause_list tmp = cl;


    while (tmp != 0){
        push(&retc, tmp->lit1, tmp->lit2, tmp->lit3);
        tmp = tmp->next;
    }
    return retc;
}

void push(clause_list* cl, literal l1, literal l2, literal l3){
    clause_list ret = (clause_list)malloc(sizeof(struct _clause_list));
    assert(ret != 0);
    
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

bool eval(clause_list* cl, literal l, bool b){
    if (*cl == 0)
        return true;

    if (!b)
        l *= -1;

    clause_list tc = *cl;

    while (tc != 0)
    {
        if (tc->lit1 == -l){ // not-literal
            tc->lit1 = 0;
            if (tc->lit2 == 0 && tc->lit2 == 0) // lazy eval for dpll
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
            if (tc == 0)
                return true;
            continue;
        }
        
        //print_literal(tc->lit1); printf(", ");print_literal(tc->lit2); printf(", ");print_literal(tc->lit3); printf("\n");
        tc = tc->next;
    }
    return true;
}

