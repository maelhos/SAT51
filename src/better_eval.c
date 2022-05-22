#include "better_eval.h"

bool better_eval(better_formula f, literal l){
    (f->vars + abs(l) - 1)->val = l > 0 ? TRUE : FALSE;
    
}