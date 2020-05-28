#include "quadtree.h"

int p1Hp = 0;
int p2Hp = 0;

QD_NODE *newBoard(int x, int y){
    QD_NODE *b = (QD_NODE*)malloc(sizeof(QD_NODE));
    b->type = QDLEAF;
    b->sw = make_point(0,0);
    b->side = (x==20)?32:64; //if x==20 then 32 else 64
    
    //As a LeafNode we set all the other quadrants as NULL
    for(int i=0;i<4;i++){
        b->node.quadrants[i] = NULL;
    }

    //maybe not needed since is started as a leaf
    b->node.leaf.cords = make_point(-1,-1);
    b->node.leaf.cell.hasShip = false;
    b->node.leaf.cell.shipType = -1;
    b->node.leaf.cell.wasHit = false;
    return b;
}

QD_NODE *insert(QD_NODE *b, Ship s){
    if(b == NULL)
        return;
    
    if(b->type == QDLEAF)
        return;

    

}


QD_NODE *getQuadrantOf(QD_NODE *b, Coordinate p){
    int halfX = (b->sw.row + b->side) / 2;
    int halfY = (b->sw.col + b->side) / 2;

    if(halfX >= p.row){
        if(halfY >= p.col)
            return b->node.quadrants[NE];
        return b->node.quadrants[SE];
    }
    if(halfY >= p.col)
        return b->node.quadrants[NW];
    return b->node.quadrants[SW];
}


QD_NODE *search(QD_NODE *b, Coordinate p){
    
    return NULL;
}


Coordinate make_point (int x, int y){
    Coordinate c;
    c.row = x;
    c.col = y;
    return c;
}

Coordinate add_point(Coordinate p, Coordinate q){
    Coordinate c;
    c.row = p.row + q.row;
    c.col = p.col + q.col;
    return c;
}

bool isEqual(Coordinate p, Coordinate q){
    if(p.row == q.row && p.col == q.col)
        return true;
    return false;
}

bool inSquare(Coordinate p, Coordinate corner, int side){
    if(corner.row + side <= p.row && corner.row >= p.row){
        if(corner.col + side <= p.col && corner.col >= p.col){
            return true;
        }
    }
    return false;
}

