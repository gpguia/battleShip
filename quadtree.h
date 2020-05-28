#include "ship.h"

#define NW 0
#define NE 1
#define SW 2
#define SE 3

typedef enum { QDNODE, QDLEAF} QD_TNODE;

typedef struct QD_Node_ {
    QD_TNODE type;    // defines the type of node (internal node or leaf)
    
    Coordinate sw;
    int side;
    union {
        struct QD_Node_ *quadrants[4];    // internal node                                               
        struct {
        Cell cell;   // VALUE --  board cell ou pointer para board cell?                                  
        Coordinate cords;    // coords of the board cell                                                             
        } leaf;     //  almost a board cell together with its coordinates
    } node;

} QD_NODE;

QD_NODE *newBoard(int x, int y);
QD_NODE *insert(QD_NODE *b, Ship s);

Coordinate make_point(int x,int y); // que constrói o ponto (x,y) e o retorna;
Coordinate add_point(Coordinate p, Coordinate q); //que retorna a adição de p a q;
bool isEqual(Coordinate p, Coordinate q); //verifica se as coordenadas coincidem);
bool inSquare(Coordinate p, Coordinate corner, int side);