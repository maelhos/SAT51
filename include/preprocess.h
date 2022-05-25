#pragma once
#include "stdinc.h"
#include "literal.h"
#include "valuation.h"
#include "clause.h"

clause_list preprocess(clause_list cl);
literal_list resolvent(literal_list ll1, literal_list ll2, literal cla);
literal clash(clause_list cl1, clause_list cl2);
