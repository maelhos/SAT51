#pragma once
#include "stdinc.h"
#include <assert.h>

typedef int32_t literal; // the literal 0 is considered always true and is ignored

void print_literal(literal l);
literal toLiteral(const char s);