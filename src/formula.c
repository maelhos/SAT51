#include "formula.h"

formula initFormula(uint16_t nbOfClauses, uint16_t nbOfVariables){
    formula ret = (formula)malloc(sizeof(struct _formula));
    ret->nbClauses = nbOfClauses;
    ret->accClauses = 0;

    ret->nbVars = nbOfVariables;

    ret->valuations = initValuations(nbOfVariables);
    ret->clauses = initClauseList();
    return ret;
}

bool pushClause(formula f, literal l1, literal l2, literal l3){
    if (f->accClauses == f->nbClauses)
        return false;
    
    f->clauses = push(f->clauses, l1, l2, l3);
    f->accClauses++;
    return true;
}
