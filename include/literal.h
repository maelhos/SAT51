#pragma once
#include "stdinc.h"
#include <assert.h>


typedef int32_t literal; // the literal 0 is considered false true and is ignored
class Literal
{

public:
    static void print_literal(literal l);
    static literal toLiteral(const char s);
};

