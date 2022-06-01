#pragma once
#include "stdinc.h"
#include "clause.h"

class preprocessor
{
private:
    static std::vector<literal> resolvent(std::vector<literal>& ll1, std::vector<literal>& ll2, literal cla);
    static literal clash(std::vector<literal>& cl1, std::vector<literal>& cl2);
public:
    static std::vector<std::vector<literal>>* preprocess(std::vector<std::vector<literal>>& cl);

};

