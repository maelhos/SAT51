#include "preprocess.h"

inline literal preprocessor::clash(std::vector<literal>& cl1, std::vector<literal>& cl2){
    literal clash = 0;
    for (int32_t i = 0; i < cl1.size(); i++)
    {
        for (int32_t j = 0; j < cl2.size(); j++)
        {
            if (cl1[i] == -cl2[j]){
                if (clash == 0)
                    clash = abs(cl1[i]);
                else
                    return 0;
            }
        }
    }
    return clash;
}
inline std::vector<literal> preprocessor::resolvent(std::vector<literal>& ll1, std::vector<literal>& ll2, literal cla){
    std::vector<literal>* ret = new std::vector<literal>;

    for (int32_t i = 0; i < ll1.size(); i++)
    {
        if (abs(ll1[i]) != cla)
            ret->push_back(ll1[i]);
    }
    for (int32_t i = 0; i < ll2.size(); i++)
    {
        if (abs(ll2[i]) != cla)
            ret->push_back(ll2[i]);
    }
    return *ret;
}

std::vector<std::vector<literal>>* preprocessor::preprocess(std::vector<std::vector<literal>>& cl){
    std::vector<std::vector<literal>>* ret = new std::vector<std::vector<literal>>(cl);

    for (int32_t i = 0; i < cl.size(); i++)
    {
        for (int32_t j = i + 1; j < cl.size(); j++)
        {
            literal cla = clash(cl[i], cl[j]);
            if (cla)
                ret->push_back(resolvent(cl[i], cl[j], cla));
        }
    }
    return ret;
}