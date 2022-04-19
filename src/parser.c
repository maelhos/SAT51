#include "parser.h"

formula parser(FILE* f){
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    uint32_t lineNumber = 1;

    bool isFormulaDefined = false;

    char buffTypeChar = 0;
    char tp[3] = {0};
    uint32_t indexchar = 0;

    formula fret = NULL;
    while ((read = getline(&line, &len, f)) != -1) {
        buffTypeChar = line[indexchar];
        while (buffTypeChar == ' '){
            indexchar++;
            buffTypeChar = line[indexchar];
        }
        if (buffTypeChar == '\n' || buffTypeChar == 'c')
            continue;
        if (buffTypeChar == 'p'){
            if (isFormulaDefined){
                printf("\"%s\"\n",line);
                for (uint32_t i = 0; i < indexchar; i++)
                    printf(" ");
                printf("^\n");
                printf("Syntax error in CNF file, \"p cnf {} {}\" already defined...\n");
                exit(EXIT_FAILURE);
            }
            else{
                isFormulaDefined = true;

            }
        }
        else{
            printf("\"%s\"\n",line);
            for (uint32_t i = 0; i < indexchar; i++)
                printf(" ");
            printf("^\n");
            printf("Syntax error in CNF file, unrecognized token ...");
            exit(EXIT_FAILURE);
        }
        indexchar = 0;
        lineNumber++;
    }
}