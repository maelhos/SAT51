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

bool pushClause(formula f, literal l1, literal l2, literal l3){
    if (f->accClauses == f->nbClauses)
        return false;
    
    f->clauses = push(f->clauses, l1, l2, l3);
    f->accClauses++;
    return true;
}

void print_formula(formula f){
    printf("--- %d variables with %d / %d clauses remaining ---\n", f->nbVars, f->accClauses, f->nbClauses);
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
    while (cl != 0){
        if (cl->clauseVal == TRUE){
            cl = cl->next;
            continue;
        }
        
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
        if (cl->clauseVal == TRUE)
           printf("[1]");
        else if (cl->clauseVal == FALSE)
            printf("[0]");
        else
            printf("[?]");
        cl = cl->next;
    }
    if (first){
        printf("<SAT>");
    }
    
    printf("\n--- end ---\n");
}

valuation evalAtLiteral(formula f, literal l, bool value){
    assert(0 < l && l < f->nbVars + 1);
    f->valuations[l] = (valuation)value;
    clause_list tmp = f->clauses;
    if (!value)
        l *= -1;
    
    while (tmp != 0)
    {
        if (tmp->clauseVal == TRUE) // those are "removed"
        {
            tmp = tmp->next;
            continue;
        }
        
        if (tmp->lit1 == -l){ // not-literal
            tmp->lit1 = 0;
            if (tmp->lit2 == 0 && tmp->lit2 == 0) // lazy eval
                return FALSE;
        }
        else if (tmp->lit2 == -l){
            tmp->lit2 = 0;
            if (tmp->lit2 == 0 && tmp->lit2 == 0) // lazy eval
                return FALSE;
        }
        else if (tmp->lit3 == -l){
            tmp->lit3 = 0;
            if (tmp->lit2 == 0 && tmp->lit2 == 0) // lazy eval
                return FALSE;
        }
        else if (tmp->lit1 == l || tmp->lit2 == l || tmp->lit3 == l){ // actual literal
            tmp->clauseVal = TRUE;
        }
        tmp = tmp->next;
    }
    
}