#include "stdinc.h"
#include "formula.h"
#include "parser.h"
#include "quine.h"

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
        print_formula(f);

        fclose(filecnf);
    }
    
    return EXIT_SUCCESS;
}