#include <stdbool.h>

typedef struct _Coordinate{
    int row;
    int col;
}Coordinate;


enum ShipType{
    CARRIER,  //5
    BATTLESHIP, //4
    CRUISER,   //3
    SUBMARINE,  //3
    DESTROYER  //2
};

typedef struct _Ship{
    int type;
    int length;
    Coordinate start;
    Coordinate end;
    bool isAlive;
} Ship;