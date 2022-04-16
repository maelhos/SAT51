#include "literal.h"


void print_literal(literal l){
    if (l < 0){
        printf("!");
        l *= -1;
    }
    char c = (l % 26) + 'a' - 1;
    char nb = (l / 26) + '0';
    printf("%c", c);
    if (!nb)
        printf("%c", nb);
}