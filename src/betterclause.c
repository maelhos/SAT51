#include "betterclause.h"

void print_better_formula(better_formula f){
    printf("--- %d variables with %d clauses ---\n-(better formula used)-\n", f->nbVars, f->nbClauses);
    for (uint32_t i = 0; i < f->nbVars; i++)
    {
        printf("%d :\n", i + 1);
        better_clause_list tposHeadList = (f->vars + i)->posHeadList;
        better_clause_list tnegHeadList = (f->vars + i)->negHeadList;
        better_clause_list tposTailList = (f->vars + i)->posTailList;
        better_clause_list tnegTailList = (f->vars + i)->negTailList;
        printf("    posHeadList :");
        print_bl(tposHeadList);
        printf("\n");
        printf("    negHeadList :");
        print_bl(tnegHeadList);
        printf("\n");
        printf("    posTailList :");
        print_bl(tposTailList);
        printf("\n");
        printf("    negTailList :");
        print_bl(tnegTailList);

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

    literal_list templl = 0;

    while (cl != 0 ){
        pushll(&templl, cl->lit3); // reverse order such that lit1 is on top of stack
        pushll(&templl, cl->lit2);
        pushll(&templl, cl->lit1);

        (ret->vars + abs(cl->lit1) - 1)->val = UNKNOWN;
        if (cl->lit1 > 0)
            pushbl(&((ret->vars + cl->lit1 - 1)->posHeadList), templl);
        else
            pushbl(&((ret->vars - cl->lit1 - 1)->negHeadList), templl);

        if (cl->lit3 > 0)
            pushbl(&((ret->vars + cl->lit3 - 1)->posTailList), templl);
        else
            pushbl(&((ret->vars - cl->lit3 - 1)->negTailList), templl);
        templl = 0;
        cl = cl->next;
    }

    return ret;
}