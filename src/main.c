#include "stdinc.h"
#include "formula.h"
#include "parser.h"
#include "quine.h"
#include "DPLL.h"
#include "clause.h"
#include "better_clause.h"
#include <time.h>

int main(int argc, char** argv){
    srand(time(NULL));
    if (argc == 2){
        char* path = argv[1];
        FILE* filecnf = fopen(path, "r");
        if (filecnf == 0)
        {
            printf("CNF file %s not found or does not have permition ...\n", path);
            exit(EXIT_FAILURE);
        }
        formula f = parse(filecnf);
        //better_formula fp = convert(f);
        //print_better_formula(fp);
        printf("%d\n",DPLL(f));
        
        for (uint32_t i = 0; i < f->nbVars; i++){
            beval(&f->clauses, i + 1, f->valuations[i]);
        }
    
        printcl(f->clauses);
        printValAsCNF(f->valuations, f->nbVars);

    }
    
    return EXIT_SUCCESS;
}