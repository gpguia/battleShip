#include <stdbool.h>


#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define CRUSIER_SIZE 3
#define SUBMARINE_SIZE 3
#define DESTROYER_SIZE 2

typedef struct _Coordinate{
    int row;
    int col;
}Coordinate;

enum ShipType{
    CARRIER,  //0
    BATTLESHIP, //1
    CRUISER,   //2
    SUBMARINE,  //3
    DESTROYER  //4
};

typedef struct _Ship{
    int type;
    int length;
    Coordinate start;
    bool isAlive;
    bool isHorizontal;
    int shotsRecived;
} Ship;
