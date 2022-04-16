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

void print_formula(formula f){
    printf("--- %d variables with %d / %d clauses satisfied ---\n", f->nbVars, f->accClauses, f->nbClauses);
    printf("Valuations :\n");
    for (uint16_t i = 0; i < f->nbVars; i++)
    {
        print_literal(i);
        printf(" -> ");
        printValuation(f->valuations[i]);
        printf("\n");
    }
    printf("\n Formula :\n");
    clause_list cl = f->clauses;
    bool first = true;
    while (cl != 0){
        if (first)
            first = false;
        else
            printf(" || ");
        printf("(");
        print_literal(cl->lit1);
        printf(" || ");
        print_literal(cl->lit2);
        printf(" || ");
        print_literal(cl->lit3);
        printf("(");
        printf(" || ");
        cl = cl->next;
    }
    if (first){
        printf("<SAT>");
    }
    
    printf("\n--- end ---\n");
}