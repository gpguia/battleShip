#include "ship.h"

#define NW 0
#define NE 1
#define SW 2
#define SE 3

typedef enum { QDNODE, QDLEAF} QD_TNODE;

typedef struct QD_Node_ {
    QD_TNODE type;    // defines the type of node (internal node or leaf)
    
    Coordinate topLeft;
    Coordinate botRight;
    union {
        struct QD_Node_ *quadrants[4];    // internal node                                               
        struct {
            Cell cell;   // VALUE --  board cell ou pointer para board cell?                                  
            Coordinate cords;    // coords of the board cell                                                             
        } leaf;     //  almost a board cell together with its coordinates
    } node;

} QD_NODE;

QD_NODE *newQuadLeaf(Coordinate topL, Coordinate botR);
QD_NODE *newQuadNode(Coordinate topL, Coordinate botR);
QD_NODE *search(QD_NODE *b, Coordinate p);
QD_NODE *insertCords(QD_NODE *b, Coordinate p, int shipType);
Coordinate make_point(int x,int y); // que constrói o ponto (x,y) e o retorna;
bool inBoundary(QD_NODE *b, Coordinate p);
bool isValidPos(QD_NODE *b, Coordinate p);

void sumShipSizesAndSetHP(int *lstOfShips, int* p1Hp, int *p2Hp);
void randomPlaceShips(QD_NODE *b, int *lst);

void printTree(QD_NODE *b, int x, int y);
int getQuadrant(QD_NODE *b, Coordinate p);