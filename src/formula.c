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

void pushClause(formula f, literal l1, literal l2, literal l3){
    push(&(f->clauses), l1, l2, l3);
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
    clause_list cl = f->clauses;

    bool first = true;
    if (cl == 0)
        printf("SAT");
    else{
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
    }
    printf("\n--- end ---\n");
}
