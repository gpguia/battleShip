#include "utils.h"

typedef struct _Shots{
    Coordinate target;
    bool isHit;
    struct _Shots* next;
} Shots;



Shots* newShot(Shots* lst, Coordinate s, bool isHit);
void clearShots(Shots *lst);
Shots* searchShot(Shots* lst, Coordinate k);
void printShots(Shots* lst);