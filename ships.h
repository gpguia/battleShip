#include <stdbool.h>
#include <stdlib.h>


#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define CRUSIER_SIZE 3
#define SUBMARINE_SIZE 3
#define DESTROYER_SIZE 2
#define TSHAPE_SIZE 3
#define GOODSHOT 6

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
    TSHAPE  //5
};

typedef struct _Ship{
    int type;
    int length;
    Coordinate start;
    bool isAlive;
    bool isHorizontal;
    int shotsRecived;
} Ship;


struct _Ships{
    Ship ship;
    struct _Ships* next;
};
typedef struct _Ships Ships;


struct _Shots{
    Coordinate target;
    bool isHit;
    struct _Shots* next;
};
typedef struct _Shots Shots;

Ships* searchLivingShips(Ships* lst, int shipType);
Ships* newShip(Ships* lst, Ship s);
void clearShips(Ships* lst);

Shots* newShot(Shots* lst, Coordinate s, bool isHit);
void clearShots(Shots *lst);
Shots* searchShot(Shots* lst, Coordinate k);