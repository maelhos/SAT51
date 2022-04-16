#include "stdinc.h"
#include "formula.h"

int main(int argc, char** argv){
    formula f = initFormula(2, 3);
    print_formula(f);
    printf("Hello Pastis !\n");
    return 0;
}