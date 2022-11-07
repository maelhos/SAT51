#include "formula.h"

formula::formula()
{
    p_valuations = 0;
    p_nbVars = 0;
    p_nbClauses = 0;
}


formula::~formula()
{
}

void formula::initFormula(uint32_t nbOfClauses, uint32_t nbOfVariables){
    p_nbClauses = nbOfClauses;

    p_nbVars = nbOfVariables;

    p_valuations = v_initValuations(nbOfVariables);
}

formula* formula::copy(){
    formula* ret = new formula();
    ret->initFormula(p_nbClauses, p_nbVars);

    ret->p_valuations = v_copyValuations(p_valuations, p_nbVars);
    ret->p_clauses = *p_clauses.copy();
    return ret; 
}

void formula::pushClause(std::vector<literal> lits){
    p_clauses.p_CL->push_back(lits);
}

void formula::print_formula(){
    printf("--- %d variables with %d clauses ---\n", p_nbVars, p_nbClauses);
    printf("Valuations :\n");
    for (uint32_t i = 0; i < p_nbVars; i++)
    {
        Literal::print_literal(i+1);
        printf(" -> ");
        v_printValuation(p_valuations[i]);
        printf("\n");
    }
    printf("\nFormula :\n");
    p_clauses.printcl();
    printf("--- end ---\n");
}
