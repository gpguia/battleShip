#include "shots.h"

Shots* newShot(Shots* lst, Coordinate s, bool isHit){
    Shots* node = (Shots*)malloc(sizeof(Shots));
    if(node != NULL){
        node->next = lst;
        node->target.row = s.row;
        node->target.col = s.col;
        node->isHit=isHit;
    }
    return node;
}

Shots* searchShot(Shots* lst, Coordinate k){
    Shots* p;
    for(p=lst; p!=NULL; p = p->next){
        if(p->target.row == k.row && p->target.col == k.col){
            return p;
        }
    }
    return NULL;
}

void clearShots(Shots *lst){
    Shots* s = lst, *aux;
    while(s != NULL){
        aux = s->next;
        free(s);
        s = aux;
    }
}

void printShots(Shots* lst){
    Shots* s;
    printf(KMAG "Shots fired: ");
    for(s = lst; s != NULL; s = s->next){
        if(s->isHit){
            printf(KGRN "(%d,%d) ",s->target.row,s->target.col);
        }else{
            printf(KRED "(%d,%d) ",s->target.row,s->target.col);
        }
    }
    printf(KNRM "\n");
}