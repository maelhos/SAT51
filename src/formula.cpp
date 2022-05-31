#include "formula.h"

formula initFormula(uint32_t nbOfClauses, uint32_t nbOfVariables){
    formula ret = (formula)malloc(sizeof(struct _formula));
    ret->nbClauses = nbOfClauses;

    ret->nbVars = nbOfVariables;

    ret->valuations = initValuations(nbOfVariables);
    ret->clauses = 0;
    return ret;
}

formula copy(formula f){
    formula ret = (formula)malloc(sizeof(struct _formula));
    ret->nbClauses = f->nbClauses;

    ret->nbVars = f->nbVars;

    ret->valuations = copyValuations(f->valuations, f->nbVars);
    ret->clauses = copyClauses(f->clauses);
    return ret; 
}

void pushClause(formula f, literal_list lits){
    push(&(f->clauses), lits);
}

void print_formula(formula f){
    printf("--- %d variables with %d clauses ---\n", f->nbVars, f->nbClauses);
    printf("Valuations :\n");
    for (uint32_t i = 0; i < f->nbVars; i++)
    {
        print_literal(i+1);
        printf(" -> ");
        printValuation(f->valuations[i]);
        printf("\n");
    }
    printf("\nFormula :\n");
    printcl(f->clauses);
    printf("\n--- end ---\n");
}
