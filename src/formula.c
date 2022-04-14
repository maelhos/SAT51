#include "formula.h"

formula initFormula(uint16_t nbOfClauses, uint16_t nbOfVariables){
    formula ret = (formula)malloc(sizeof(struct _formula));
    ret->nbClauses = nbOfClauses;
    ret->nbVars = nbOfVariables;

    ret->valuations = initValuations(nbOfVariables);
    ret->clauses = initClauseList();
    return ret;
}