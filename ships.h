

typedef struct _Coordinate{
    int row;
    int col;
}Coordinate;


enum ShipType{
    CARRIER, 
    BATTLESHIP,
    CRUISER, 
    SUBMARINE,
    DESTROYER
};

typedef struct _Ship{
    int type;
    int length;
    Coordinate start;
    Coordinate end;
    bool isAlive;
} Ship;