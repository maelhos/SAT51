#pragma once
#include "stdinc.h"
#include "literal.h"

struct _clause_list
{
    struct _clause_list* next;
    literal lit1;
    literal lit2;
    literal lit3;
};

typedef struct _clause_list* clause_list;

clause_list initClauseList();