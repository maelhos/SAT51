#include "watchedLiterals.h"

partialFrame::partialFrame(uint32_t l, uint8_t o, uint8_t n, uint8_t t) : lit(l), oldval(o), newval(n), type(t)
{
}

partialFrame::~partialFrame()
{
}

void partialFrame::collapse(uint8_t* state){
    state[lit - 1] = oldval;
}

watchedformula::watchedformula(formula& f){
    nbClauses = f.p_nbClauses;
    nbVars = f.p_nbVars;
    state = new uint8_t[nbVars];
    posWatched = new std::vector<watchedClause>[nbVars];
    negWatched = new std::vector<watchedClause>[nbVars];

    for (uint32_t i = 0; i < nbVars; i++)
        state[i] = UNKNOWN;
    
    std::vector<std::vector<int>> pcl = *f.p_clauses.p_CL;
    for (uint32_t i = 0; i < nbClauses; i++)
    {
        if (pcl[i].size() == 1){ // special case... stupid clause
            if (pcl[i][0] > 0){
                posWatched[pcl[i][0] - 1].push_back(pcl[i]);
            }
            if (pcl[i][0] < 0){
                negWatched[-pcl[i][0] - 1].push_back(pcl[i]);
            }
            continue;
        }

        if (pcl[i][0] > 0)
            posWatched[pcl[i][0] - 1].push_back(pcl[i]);

        if (pcl[i][1] > 0)
            posWatched[pcl[i][1] - 1].push_back(pcl[i]);

        if (pcl[i][0] < 0)
            negWatched[-pcl[i][0] - 1].push_back(pcl[i]);

        if (pcl[i][1] < 0)
            negWatched[-pcl[i][1] - 1].push_back(pcl[i]);
    }
}

void watchedformula::print(){
    printf("--- %d variables with %d clauses ---\n", nbVars, nbClauses);
    for (uint32_t i = 0; i < nbVars; i++)
    {
        std::cout << "Pos watched for lit " << i+1 << " eval :"; 
        valuation(state[i]).printValuation();
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
    printf("\n--- end ---\n");
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
            if (!eval(toBePropag[i], stack, PF_PROPAG))
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

int32_t watchedformula::findBasicUnit(){
    for (uint32_t i = 0; i < nbVars; i++)
    {
        for (uint32_t j = 0; j < posWatched[i].size(); j++)
        {
            if (posWatched[i][j].size() == 1 && state[abs(posWatched[i][j][0]) - 1] == UNKNOWN)
                return posWatched[i][j][0];
            
        }
        for (uint32_t j = 0; j < negWatched[i].size(); j++)
        {
            if (negWatched[i][j].size() == 1 && state[abs(negWatched[i][j][0]) - 1] == UNKNOWN)
                return negWatched[i][j][0];
            
        }
    }
    return 0;
}

uint8_t watchedformula::val(uint32_t index){
    return state[index];
}
watchedformula::~watchedformula(){
}