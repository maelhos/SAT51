#include "parser.h"

parser::parser(FILE* f) : p_file(f)
{
}

parser::~parser()
{
}

void parser::printError(char* line, const char* mess, uint32_t lineNumber, uint32_t indexchar){
    printf(">>> %s",line);
    for (uint32_t i = 0; i < indexchar + 4; i++)
        printf(" ");
    printf("^^^\n");
    printf(mess, lineNumber, indexchar + 1);
    exit(EXIT_FAILURE);
}

void parser::gotoNextNonspace(uint32_t* index, char* buffFirstChar, char* line){
    while (*buffFirstChar == ' '){
        (*index)++;
        *buffFirstChar = line[*index];
    }
}
 
formula parser::parse(){
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    uint32_t lineNumber = 1;

    bool isFormulaDefined = false;

    char buffTypeChar = 0;
    uint32_t indexchar = 0;

    formula* fret = new formula();
    while ((read = getline(&line, &len, p_file)) != -1) {
        buffTypeChar = line[indexchar];

        gotoNextNonspace(&indexchar, &buffTypeChar, line);

        if (buffTypeChar == '\n' || buffTypeChar == 'c'){ // if empty line or 'c' for comment do nothing and go next line
            indexchar = 0;
            lineNumber++;
            continue;
        }
        
        if (buffTypeChar == '%')
            break;
        if (buffTypeChar == 'p'){ // if we have a formula definition line
            if (isFormulaDefined){ // THERE CAN ONLY BE ONE HIGHLANDER
                printError(line,
                "Syntax error in CNF file, \"p cnf {} {}\" already defined at line %d on char %d...\n",
                lineNumber,
                indexchar);
            }
            else{
                isFormulaDefined = true; // highlanders remembers ...

                indexchar++;
                buffTypeChar = line[indexchar];
                gotoNextNonspace(&indexchar, &buffTypeChar, line);

                if (strncmp(line + indexchar, "cnf", 3)){ // check for DIMACS formula type ... even if almost only cnf exist
                    printError(line,
                    "Syntax error in CNF file, only \"cnf\" format is supported for DIMACS at line %d on char %d...\n",
                    lineNumber,
                    indexchar);
                }

                indexchar += 3;
                buffTypeChar = line[indexchar];
                gotoNextNonspace(&indexchar, &buffTypeChar, line);
                char* end = 0;

                int32_t tempvars = strtol(line + indexchar, &end, 10); // get nb of vars
                int32_t tempclauses = strtol(end, 0, 10); // get nb of clauses
                
                if (tempvars < 0){ // i mean...
                    printError(line,
                    "Syntax error in CNF file, negative number of variables, have you ever had -5 apples ? at line %d on char %d...\n",
                    lineNumber,
                    indexchar);
                }
                if (tempclauses < 0){ // i mean...
                    printError(line,
                    "Syntax error in CNF file, negative number of clauses, have you ever had -5 apples ? at line %d on char %d...\n",
                    lineNumber,
                    (uint32_t)(end - line + 1)); // kinda hacky ... 
                }

                if (tempvars == 0 || tempclauses == 0) // if no variables or clauses ... the formula is ... SAT
                {
                    printf("s SATISFIABLE\n(0 variables 0 clauses or wrong numbers...)\n");
                    exit(EXIT_SUCCESS);
                }
                fret->initFormula(tempclauses, tempvars);
            }
        }
        else {
            if (isFormulaDefined)
            {
                int32_t templit;

                char* end = 0;
                char* start = 0;
                std::vector<literal>* tl = new std::vector<literal>();

                while (true){
                    gotoNextNonspace(&indexchar, &buffTypeChar, line);
                    start = line + indexchar;
                    if (*(line+indexchar) == '0')
                        break;
                    if (*(line+indexchar) == '\n' || *(line+indexchar) == 0)
                        printError(line,
                            "Syntax error in CNF file, every clause should end with ' 0' at line %d on char %d...\n",
                            lineNumber,
                            indexchar);
                    templit = strtol(line + indexchar, &end, 10);
                    indexchar += (uint32_t)(end - start + 1);
                    if (templit == 0)
                        printError(line,
                            "Syntax error in CNF file, first literal seem wrong (expect space separated int) at line %d on char %d...\n",
                            lineNumber,
                            indexchar);
                    tl->push_back(templit);
                }
                
                fret->pushClause(*tl);
            }
            else
                printError(line,
                    "Syntax error in CNF file, unrecognized token at line %d on char %d...\n",
                    lineNumber,
                    indexchar);
        }
        indexchar = 0;
        lineNumber++;
    }
    return *fret;
}