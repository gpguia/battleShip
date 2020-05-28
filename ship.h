#include "utils.h"

#define MAXNUMSHIPS 16
#define CARRIER_SIZE 5
#define TSHAPE_SIZE 3 //+2 for the front part
#define BATTLESHIP_SIZE 4
#define CRUSIER_SIZE 3
#define SUBMARINE_SIZE 3
#define DESTROYER_SIZE 2
#define ROTATION_0 0
#define ROTATION_90 1
#define ROTATION_180 2
#define ROTATION_270 3

typedef struct _Coordinate{
    int row;
    int col;
}Coordinate;

enum ShipType{
    CARRIER,  //0
    BATTLESHIP, //1
    CRUISER,   //2
    SUBMARINE,  //3
    DESTROYER,  //4
    TSHAPE,  //5
    GOODSHOT, //hit the target
    WATERSHOT
};

typedef struct _Shots{
    Coordinate target;
    bool isHit;
    struct _Shots* next;
} Shots;

typedef struct _Cell{
    bool hasShip;
    bool wasHit;
    int shipType;
} Cell;

typedef struct _Ship{
    int type;
    int length;
    Coordinate start;
    int rotation;
} Ship;
