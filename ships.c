#include "ships.h"

Ships* newShip(Ships* lst, Ship s){
    Ships* node = (Ships*)malloc(sizeof(Ships));
    if(node != NULL){
        node->next = lst;
        node->ship = s;
    }
    return node;
}

Ships* searchLivingShips(Ships* lst, int shipType){
    Ships* s;
    for(s = lst; s != NULL; s = s->next){
        if(s->ship.type == shipType && s->ship.isAlive == true){
            return s;
        }
    }
    return NULL;
}

void clearShips(Ships* lst){
    Ships* s = lst, *aux;
    while(s != NULL){
        aux = s->next;
        free(s);
        s = aux;
    }
}

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