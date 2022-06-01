#include "literal.h"


void Literal::print_literal(literal l){
    if (l == 0){
        printf("F");
        return;
    }
    
    if (l < 0){
        printf("!");
        l *= -1;
    }
    char c = (l % 26) + 'a' - 1;
    char nb = (l / 26) + '0';
    printf("%c", c);
    if (nb != '0')
        printf("%c", nb);
}

literal Literal::toLiteral(const char s){
    if ('a' <= s && s <= 'z' )
        return s - 'a' + 1;
    else 
        return 0;
}