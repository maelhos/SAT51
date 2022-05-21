#include "betterclause_list.h"

void pushll(literal_list* cl, literal l){
    literal_list ret = (clause_list)malloc(sizeof(struct _literal_list));
    
    if (*cl == 0){
        ret->next = 0;
        ret->previous = 0;
    }
    else{
        ret->next = *cl;
        ret->previous = 0;
        (*cl)->previous = ret;
    }
    ret->lit = l;
    *cl = ret;
}
literal_list popll(literal_list l, literal_list* hd){
    literal_list ret;
    if (l == 0)
        return 0;
    if (l->next == 0)
        if (l->previous == 0){ // only one element7
            *hd = 0;
            ret = 0;
        }
        else{ // ending element
            l->previous->next = 0;
            ret = l->previous;
        }
    else{
        l->next->previous = l->previous;
        if (l->previous != 0){ // normal case in the middle
            l->previous->next = l->next;
            ret = l->previous;
        }
        else{ // head with non empty tail
            l->next->previous = 0;
            ret = l->next;
            *hd = (*hd)->next;
        }
    }
    free(l);
    return ret;
}

void pushbl(better_clause_list* cl, literal_list ll){
    better_clause_list ret = (clause_list)malloc(sizeof(struct _better_clause_list));
    
    if (*cl == 0){
        ret->next = 0;
        ret->previous = 0;
    }
    else{
        ret->next = *cl;
        ret->previous = 0;
        (*cl)->previous = ret;
    }
    ret->headIndex = 0;
    ret->tailIndex = ll->length - 1;
    ret->literals = ll;
    *cl = ret;
}
better_clause_list popbl(better_clause_list l, better_clause_list* hd){
    better_clause_list ret;
    if (l == 0)
        return 0;
    if (l->next == 0)
        if (l->previous == 0){ // only one element7
            *hd = 0;
            ret = 0;
        }
        else{ // ending element
            l->previous->next = 0;
            ret = l->previous;
        }
    else{
        l->next->previous = l->previous;
        if (l->previous != 0){ // normal case in the middle
            l->previous->next = l->next;
            ret = l->previous;
        }
        else{ // head with non empty tail
            l->next->previous = 0;
            ret = l->next;
            *hd = (*hd)->next;
        }
    }
    free(l);
    return ret;
}