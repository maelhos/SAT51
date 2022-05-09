#include "stdinc.h"
#include "formula.h"
#include "parser.h"
#include "quine.h"
#include "DPLL.h"
#include "clause.h"

int main(int argc, char** argv){
    if (argc == 2){
        char* path = argv[1];
        FILE* filecnf = fopen(path, "r");
        if (filecnf == 0)
        {
            printf("CNF file %s not found or does not have permition ...\n", path);
            exit(EXIT_FAILURE);
        }
        formula f = parse(filecnf);


        printf("%d\n",quine(f));
        
        for (uint32_t i = 0; i < f->nbVars; i++){
            beval(&f->clauses, i + 1, f->valuations[i]);
        }
        
        printcl(f->clauses);
        printValAsCNF(f->valuations, f->nbVars);

        //printcl(f->clauses);
        //beval(&f->clauses, 1, false);
        //beval(&f->clauses, 2, false);
        //printf("\n");
        //printcl(f->clauses);
        //
        //unit_propagate(&f->clauses, f->valuations);
        //printf("\n");
        //printcl(f->clauses);
        //printValAsCNF(f->valuations, f->nbVars);
        //fclose(filecnf);
    }
    
    return EXIT_SUCCESS;
}