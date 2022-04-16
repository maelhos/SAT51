#include "clause.h"

clause_list initClauseList(){
    return 0;
}

clause_list push(clause_list cl, literal l1, literal l2, literal l3){
    clause_list ret = (clause_list)malloc(sizeof(struct _clause_list));
    ret->vl = UNKNOWN;
    ret->next = cl;
    ret->lit1 = l1;
    ret->lit2 = l2;
    ret->lit3 = l3;

    return ret;
}