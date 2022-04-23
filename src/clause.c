#include "clause.h"

clause_list initClauseList(){
    return 0;
}

clause_list copyClauses(clause_list cl){
    clause_list retc = initClauseList(); // lol
    clause_list tmp = cl;
    while (tmp != 0)
    {
        retc = push(retc, tmp->lit1, tmp->lit2, tmp->lit3);
        tmp = tmp->next;
    }
    return retc;
}

clause_list push(clause_list cl, literal l1, literal l2, literal l3){
    clause_list ret = (clause_list)malloc(sizeof(struct _clause_list));
    
    if (cl == 0){
        ret->next = ret;
        ret->previous = ret;
    }
    else{

    }
    ret->lit1 = l1;
    ret->lit2 = l2;
    ret->lit3 = l3;
    
}

void pop(clause_list* cl){
    if ((*cl)->previous == 0)
        *cl = (*cl)->next;
    else{
        (*cl)->previous = 
    }
    
}