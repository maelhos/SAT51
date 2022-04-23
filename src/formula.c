#include "formula.h"

formula initFormula(uint32_t nbOfClauses, uint32_t nbOfVariables){
    formula ret = (formula)malloc(sizeof(struct _formula));
    ret->nbClauses = nbOfClauses;
    ret->accClauses = 0;

    ret->nbVars = nbOfVariables;

    ret->valuations = initValuations(nbOfVariables);
    ret->clauses = initClauseList();
    return ret;
}

formula copy(formula f){
    formula ret = (formula)malloc(sizeof(struct _formula));
    ret->nbClauses = f->nbClauses;
    ret->accClauses = f->accClauses;

    ret->nbVars = f->nbVars;

    ret->valuations = copyValuations(f->valuations, f->nbVars);
    ret->clauses = copyClauses(f->clauses);
    return ret; 
}

void pushClause(formula f, literal l1, literal l2, literal l3){
    f->clauses = push(f->clauses, l1, l2, l3);
    f->accClauses++;
}

void print_formula(formula f){
    printf("--- %d variables with %d / %d clauses ---\n", f->nbVars, f->accClauses, f->nbClauses);
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
    for (uint32_t i = 0; i < f->accClauses; i++){
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
    }
    if (first){
        printf("<SAT>");
    }
    
    printf("\n--- end ---\n");
}

bool evalAtLiteral(formula f, literal l, bool value){
    if (!(0 < l && l < f->nbVars + 1))
        return true;
    f->valuations[l-1] = (valuation)value;
    clause_list tmp = f->clauses;
    if (!value)
        l *= -1;
    
    if (tmp == 0)
        return true;

    uint32_t len_init = f->accClauses;
    for (uint32_t i = 0; i < len_init; i++){
        if (tmp->lit1 == -l){ // not-literal
            if (tmp->lit2 == 0 && tmp->lit2 == 0) // lazy eval
                return false;
            tmp->lit1 = 0;
        }
        else if (tmp->lit2 == -l){
            if (tmp->lit1 == 0 && tmp->lit3 == 0) // lazy eval
                return false;
            tmp->lit2 = 0;
        }
        else if (tmp->lit3 == -l){
            if (tmp->lit1 == 0 && tmp->lit2 == 0) // lazy eval
                return false;
            tmp->lit3 = 0;
        }
        else if (tmp->lit1 == l || tmp->lit2 == l || tmp->lit3 == l){ // actual literal
            f->accClauses--;
            pop(&tmp);
            if (tmp == 0)
                return true;
        }
        tmp = tmp->next;
    }
    f->clauses = tmp; // we reassign cuz order doesnt matter and if head got chopped of we need to update pointer
    // or else we might point on a freed adress (bad)
        
    return true;
}