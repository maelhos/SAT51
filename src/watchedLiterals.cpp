#include "watchedLiterals.h"

partialFrame::partialFrame(uint32_t l, uint8_t o, uint8_t n, uint8_t t) : lit(l), oldval(o), newval(n), type(t)
{
}

partialFrame::~partialFrame()
{
}

void partialFrame::prints(){
    std::cout << "[";
    Literal::print_literal(lit);
    std::cout << ", ";
    v_printValuation(oldval);
    std::cout << "→";
    v_printValuation(newval);
    if (type == PF_CHOICE)
        std::cout << ", PF_CHOICE]";
    else
        std::cout << ", PF_PROPAG]";
}

void printStack(std::vector<partialFrame>* stack){
    std::cout << "Stack: ->";
    for (uint32_t i = 0; i < stack->size(); i++){
        (*stack)[i].prints();
        if (i != stack->size() - 1)
            std::cout << " -> ";
    }
    std::cout << "\n";

}

void partialFrame::collapse(uint8_t* state){
    state[lit - 1] = oldval;
}

watchedformula::watchedformula(formula& f){
    nbClauses = f.p_nbClauses;
    nbVars = f.p_nbVars;
    state = f.p_valuations;
    posWatched = new std::vector<watchedClause>[nbVars];
    negWatched = new std::vector<watchedClause>[nbVars];

    std::vector<std::vector<int>> pcl = *f.p_clauses.p_CL;
    for (uint32_t i = 0; i < nbClauses; i++)
    {
        if (pcl[i].size() < 2){ // special case... stupid clause
            printf(RED "No unit clause or empty is allowed during watched litteral iteration !!\n" NC);
            exit(EXIT_FAILURE);
        }

        if (pcl[i][0] > 0)
            posWatched[pcl[i][0] - 1].push_back(watchedClause(pcl[i]));

        if (pcl[i][1] > 0)
            posWatched[pcl[i][1] - 1].push_back(watchedClause(pcl[i]));

        if (pcl[i][0] < 0)
            negWatched[-pcl[i][0] - 1].push_back(watchedClause(pcl[i]));

        if (pcl[i][1] < 0)
            negWatched[-pcl[i][1] - 1].push_back(watchedClause(pcl[i]));
    }
}

void watchedformula::print(){
    printf("--- %d variables with %d clauses ---\n", nbVars, nbClauses);
    for (uint32_t i = 0; i < nbVars; i++)
    {
        std::cout << "Pos watched for lit " << i+1 << " eval :"; 
        v_printValuation(state[i]);
        std::cout << std::endl;
        for (uint32_t j = 0; j < posWatched[i].size(); j++){
            posWatched[i][j].print();
            std::cout << " ";
        }
        std::cout << std::endl;
        std::cout << "Neg watched for lit " << i+1 << std::endl;
        for (uint32_t j = 0; j < negWatched[i].size(); j++){
            negWatched[i][j].print();
            std::cout << " ";
        }
        std::cout << std::endl << std::endl;
        
    }
    printf("--- end ---\n");
}

bool watchedformula::eval(int lit, std::vector<partialFrame>* stack, uint8_t type){
    partialFrame* pftemp = new partialFrame(abs(lit), state[abs(lit) - 1], lit > 0 ? TRUE : FALSE, type);
    stack->push_back(*pftemp);
    state[abs(lit) - 1] = lit > 0 ? TRUE : FALSE;

    if (lit > 0){
        std::vector<int> toBePropag;
        uint32_t s = negWatched[lit - 1].size();
        int32_t i = 0;
        for (int32_t j = 0; j < s; j++){
            switch (negWatched[lit - 1][i].eval(lit, state, negWatched[lit - 1], i, posWatched, negWatched))
            {
            case WCLAUSE_UNSAT:
                return false;
                break;
            case WCLAUSE_UNIT:
                toBePropag.push_back(negWatched[lit - 1][i].getUnit(state));
                break;
            case WCLAUSE_SAT_OR_UK_MOVE:
                i--;
                break;
            default:
                break;
            }
            i++;
        }
        for (uint32_t i = 0; i < toBePropag.size(); i++)
        {
            if (!eval(toBePropag[i], stack, PF_PROPAG)) // pb here ...
                return false;
        }
        
    }
    else{
        std::vector<int> toBePropag;
        uint32_t s = posWatched[-lit - 1].size();
        int32_t i = 0;
        for (int32_t j = 0; j < s; j++){
            switch (posWatched[-lit - 1][i].eval(lit, state, posWatched[-lit - 1], i, posWatched, negWatched))
            {
            case WCLAUSE_UNSAT:
                return false;
                break;
            case WCLAUSE_UNIT:
                toBePropag.push_back(posWatched[-lit - 1][i].getUnit(state));
                break;
            case WCLAUSE_SAT_OR_UK_MOVE:
                i--;
                break;
            default:
                break;
            }
            i++;
        }
        for (uint32_t i = 0; i < toBePropag.size(); i++)
        {
            if (!eval(toBePropag[i], stack, PF_PROPAG)) // we may can do a goto ....
                return false;
        }
    }
    return true;
}

uint8_t watchedformula::val(uint32_t index){
    return state[index];
}
watchedformula::~watchedformula(){
}