#include "better_clause.h"

void print_better_formula(better_formula f){
    printf("--- %d variables with %d clauses ---\n-(better formula used)-\n", f->nbVars, f->nbClauses);
    for (uint32_t i = 0; i < f->nbVars; i++)
    {
        printf("%d :\n", i + 1);
        better_clause_list tposWatched = (f->vars + i)->posWatched;
        better_clause_list tnegWatched = (f->vars + i)->negWatched;
        printf("    posWatched :");
        print_bl(tposWatched);
        printf("\n");
        printf("    negWatched :");
        print_bl(tnegWatched);
        printf("\n");
    }
    
    printf("\n--- end ---\n");

}

better_formula convert(formula f){
    better_formula ret = (better_formula)malloc(sizeof(struct _better_formula));
    ret->nbClauses = f->nbClauses;
    ret->nbVars = f->nbVars;

    ret->vars = (variable*)malloc(sizeof(struct _variable)*ret->nbVars);
    
    clause_list cl = f->clauses;


    while (cl != 0 ){

        (ret->vars + abs(cl->lits->lit) - 1)->val = UNKNOWN;


        if (cl->lits->next->lit > 0)
            pushbl(&((ret->vars + cl->lits->next->lit - 1)->posWatched), cl->lits);
        else
            pushbl(&((ret->vars - cl->lits->next->lit - 1)->negWatched), cl->lits);

        if (cl->lits->lit > 0)
            pushbl(&((ret->vars + cl->lits->lit - 1)->posWatched), cl->lits);
        else
            pushbl(&((ret->vars - cl->lits->lit - 1)->negWatched), cl->lits);

        cl = cl->next;
    }

    return ret;
}

void pushPVS(partial_valuation_stack* pvs, literal lit, valuation val, uint8_t choiceType){
    partial_valuation_stack ret = (partial_valuation_stack)malloc(sizeof(struct _partial_valuation_stack));
    if (*pvs == 0){
        ret->length = 1;
        ret->next = 0;
    }
    else{
        ret->length = (*pvs)->length + 1;
        ret->next = *pvs;
    }
    ret->lit = lit;
    ret->val = val;
    ret->choiceType = choiceType;
    *pvs = ret;
}

void popPVS(partial_valuation_stack* pvs){
    if (*pvs == 0)
        return;
    partial_valuation_stack ret = (*pvs)->next;
    free(*pvs);
    *pvs = ret;
}