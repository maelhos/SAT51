#include "preprocess.h"

inline literal clash(clause_list cl1, clause_list cl2){
    literal clash = 0;
    literal_list l1t = cl1->lits;
    while (l1t != 0){
        literal_list l2t = l1t->next;
        while (l2t != 0){
            if (l1t->lit == -l2t->lit){
                if (clash == 0)
                    clash = abs(l1t->lit);
                else
                    return 0;
            }
            l2t = l2t->next;
        }
        l1t = l1t->next;
    }
    return clash;
}
inline literal_list resolvent(literal_list ll1, literal_list ll2, literal cla){
    literal_list ret = 0;
    while (ll1 != 0){
        if (abs(ll1->lit) != cla)
            pushll(&ret, ll1->lit);
        ll1 = ll1->next;
    }
    while (ll2 != 0){
        if (abs(ll2->lit) != cla)
            pushll(&ret, ll2->lit);
        ll2 = ll2->next;
    }
    return ret;
}
/*
-1 4 8
1 7 2
*/

clause_list preprocess(clause_list cl){
    clause_list ret = copyClauses(cl);
    clause_list cl1t = cl;
    while (cl1t != 0){
        clause_list cl2t = cl1t->next;
        while (cl2t != 0){
            literal cla = clash(cl1t, cl2t);
            if (cla != 0)
                push(&ret, resolvent(cl1t->lits, cl2t->lits, cla));
            cl2t = cl2t->next;
        }
        cl1t = cl1t->next;
    }
    return ret;
}