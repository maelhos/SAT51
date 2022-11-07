#include "argparsing.h"

void printHelp(char* argv0){
    const char helpstring[] = "Usage: %s [options] <file>.cnf\n\nOptional arguments:\n  -h, --help\n            show this help message and exit\n  -a, --algo\n            - QUINE (does not use heuristics)\n            - DPLL\n            - CDCL  --- IN DEV\n  -e, --heuristics\n            - FS (First literal we find...)\n            - RD (Random...)\n            - JW (Jeroslow-Wang Heuristic, assign variables with high occurrence in short clauses) default for DPLL\n            - VS (VSIDS Branching, CDCL only and default for it) --- IN DEV\n            - CS (RDLCS, with Let Cp (Cn) be the number of positive (negative) occurrences, maximal Cp + Cn\n            - IS (RDLIS, maximal max(Cp, Cn))\n  -n, --no-watched-literals  --- IN DEV\n            Disable Watched literals and lazy datastructures (I don't know why you would do that...)\n  -t, --threads  --- IN DEV\n            Number of cores to use (default 1), 0 to to use all available\n  -s, --seed\n            Seed the prng, by default seeded with time(0), (usefull for benchmark)\n\nExample:\n  %s -a QUINE perf.cnf\n";

    printf(helpstring, argv0, argv0);
    exit(EXIT_SUCCESS);
}

void parseargs(int argc, char** argv, arg_state* rs){
    (*rs)->algo = ALGO_DPLL;
    (*rs)->heur = HEUR_JW;
    (*rs)->noWatchedLiterals = false;
    (*rs)->threads = 1;
    (*rs)->isCustomSeed = false;
    (*rs)->seed = time(NULL);
    (*rs)->filename = 0;

    bool isalgo = false;
    bool isheur = false;
    bool isseed = false;
    bool isfile = false;
    if (argc == 1)
        printHelp(argv[0]);

    for (int32_t i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
            printHelp(argv[0]);
        else if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "--algo")){
            if (isalgo){
                printf("ERROR: Algorithm already defined !!\n");
                exit(EXIT_FAILURE);
            }
            else{
                isalgo = true;
                if (i + 2 > argc){
                    printf("ERROR: Algorithm require a seed... !!\n");
                    exit(EXIT_FAILURE);
                }
                if (!strcmp(argv[i+1], "QUINE"))
                    (*rs)->algo = ALGO_QUINE;
                else if (!strcmp(argv[i+1], "DPLL"))
                    (*rs)->algo = ALGO_DPLL;
                else if (!strcmp(argv[i+1], "CDCL")){
                    printf("WARNING: Dev is in prep school and thus this feature may or may not be implemented in the comming year...\n");
                    exit(EXIT_SUCCESS);
                }
                else{
                    printf("ERROR: Algorithm \"%s\" does not exist...\n", argv[i+1]);
                }
            }
            i++;
        }
        else if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--heuristic")){
            if (isheur){
                printf("ERROR: Heuristic already defined !!\n");
                exit(EXIT_FAILURE);
            }
            else{
                isheur = true;
                if (i + 2 > argc){
                    printf("ERROR: Heuristic require a seed... !!\n");
                    exit(EXIT_FAILURE);
                }
                if (!strcmp(argv[i+1], "FS"))
                    (*rs)->heur = HEUR_FIRST;
                else if (!strcmp(argv[i+1], "RD"))
                    (*rs)->heur = HEUR_RANDOM;
                else if (!strcmp(argv[i+1], "JW"))
                    (*rs)->heur = HEUR_JW;
                else if (!strcmp(argv[i+1], "VS")){
                    printf("WARNING: Dev is in prep school and thus this feature may or may not be implemented in the comming year...\n");
                    exit(EXIT_SUCCESS);
                }
                else if (!strcmp(argv[i+1], "CS"))
                    (*rs)->heur = HEUR_CS;
                else if (!strcmp(argv[i+1], "IS"))
                    (*rs)->heur = HEUR_IS;
                else{
                    printf("ERROR: Heuristic \"%s\" does not exist...\n", argv[i+1]);
                    exit(EXIT_FAILURE);
                }
            }
            i++;
        }
        else if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--no-watched-literals")
              || !strcmp(argv[i], "-t") || !strcmp(argv[i], "--threads")){
            printf("WARNING: Dev is in prep school and thus this feature may or may not be implemented in the comming year...\n");
            exit(EXIT_SUCCESS);
        }
        else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--seed")){
            if (isseed){
                printf("ERROR: Seed already defined !!\n");
                exit(EXIT_FAILURE);
            }
            else{
                isseed = true;
                if (i + 2 < argc){
                    (*rs)->isCustomSeed = true;
                    char** endptr = 0;
                    (*rs)->seed = strtoul(argv[i+1], endptr, 10);
                }
                else{
                    printf("ERROR: Seed require a seed... !!\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else{
            if (isfile){
                printf("ERROR: Argument \"%s\" unrecognized...\n", argv[i]);
            }
            else{
                isfile = true;
                (*rs)->filename = (char*)malloc(strlen(argv[i])+1);
                strcpy((*rs)->filename, argv[i]);
                
            }
        }
    }

    if (!isfile){
        printf("ERROR: Require a dimacs file !!\n");
        exit(EXIT_FAILURE);
    }
    if ((*rs)->algo == ALGO_QUINE && isheur){
        printf("ERROR: Quine does not support heuristics (by definition ...)\n");
        exit(EXIT_FAILURE);
    }
}
