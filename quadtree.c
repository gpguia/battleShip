#include "quadtree.h"

QD_NODE *newQuadLeaf(Coordinate topL, Coordinate botR){
    QD_NODE *b = (QD_NODE*)malloc(sizeof(QD_NODE));
    b->type = QDLEAF;
    b->topLeft = topL;
    b->botRight = botR;
    
    //As a LeafNode we set all the other quadrants as NULL

    //maybe not needed since is started as a leaf
    b->node.leaf.cords = make_point(-1,-1);
    b->node.leaf.cell.hasShip = false;
    b->node.leaf.cell.shipType = -1;
    b->node.leaf.cell.wasHit = false;
    return b;
}

QD_NODE *newQuadNode(Coordinate topL, Coordinate botR){
    QD_NODE *b = (QD_NODE*)malloc(sizeof(QD_NODE));
    b->type = QDNODE;
    b->topLeft = topL;
    b->botRight = botR;
    Coordinate c1, c2;
    
    int halfX = (b->topLeft.row + b->botRight.row) / 2;
    int halfY = (b->topLeft.col + b->botRight.col) / 2;

    for(int i=0;i<4;i++){
        if(i == NW){
            c1 = make_point(b->topLeft.row, b->topLeft.col);
            c2 = make_point(halfX, halfY);
        }else if(i == NE){
            c1 = make_point(halfX, b->topLeft.col);
            c2 = make_point(b->botRight.row, halfY);
        }else if(i == SW){
            c1 = make_point(b->topLeft.row, halfY);
            c2 = make_point(halfX, b->botRight.col);
        }else if(i == SE){
            c1 = make_point(halfX, halfY);
            c2 = make_point(b->botRight.row, b->botRight.col);
        }
        b->node.quadrants[i] = newQuadLeaf(c1,c2);
    }
    
    return b;
}


bool isValidPos(QD_NODE *b, Coordinate p){
    if(b == NULL)
        return false;
    
    QD_NODE* aux = search(b, p);
    if(aux == NULL)
        return true;
    
    return false;
}

int getQuadrant(QD_NODE *b, Coordinate p){
    int halfX = (b->topLeft.row + b->botRight.row) / 2;
    int halfY = (b->topLeft.col + b->botRight.col) / 2;

    if(halfX >= p.row){
        if(halfY >= p.col){
            return SW;
        }else{
            return NW;
        }
    }else{
        if(halfY >= p.col){
            return SE;
        }else{
            return NE;
        }
    }
}

QD_NODE *insertCords(QD_NODE *b, Coordinate p, int shipType){
    if(b == NULL){
        
        return b;
    }
    
    if(b->type == QDLEAF){
        if(b->node.leaf.cords.row == -1){
            b->node.leaf.cords.row = p.row;
            b->node.leaf.cords.col = p.col;
            b->node.leaf.cell.shipType = shipType;
            b->node.leaf.cell.hasShip = true;
            b->node.leaf.cell.wasHit = false;
            return b;
        }

        // We cannot subdivide it anymore cus side is 1
        if (abs(b->topLeft.row - b->botRight.row) <= 1 && 
            abs(b->topLeft.col - b->botRight.col) <= 1) { 
            return b;
        }

        QD_NODE *node = newQuadNode(b->topLeft, b->botRight);
        node = insertCords(node, b->node.leaf.cords, b->node.leaf.cell.shipType);
        node = insertCords(node, p, shipType);
        return node;
    }
    
    int quad = getQuadrant(b, p);
    b->node.quadrants[quad] = insertCords(b->node.quadrants[quad], p, shipType);
    
    return b;
}

bool inBoundary(QD_NODE *b, Coordinate p){
    if(b->topLeft.row > p.row || b->topLeft.col < p.col || b->botRight.row < p.row || b->botRight.col > p.col)
        return false;
    return true;
}


QD_NODE *search(QD_NODE *b, Coordinate p){
    
    if(b == NULL)
        return NULL;

    if(b->type == QDNODE){
        int quad = getQuadrant(b, p);
        return search(b->node.quadrants[quad], p);
    }

    if(b != NULL){
        if(b->node.leaf.cords.row == p.row && b->node.leaf.cords.col == p.col){
            return b;
        }
    }

    // if(!inBoundary(b,p)){
    //     return NULL;
    // }
    
    
    // int halfX = (b->topLeft.row + b->botRight.row) / 2;
    // int halfY = (b->topLeft.col + b->botRight.col) / 2;

    // if(halfX >= p.row){
    //     if(halfY >= p.col){
    //         if(b->node.quadrants[SW] == NULL){
    //             return NULL;
    //         }
    //         return search(b->node.quadrants[SW], p);
    //     }else{
    //         if(b->node.quadrants[NW] == NULL){
    //             return NULL;
    //         }
    //         return search(b->node.quadrants[NW], p);
    //     }
    // }else{
    //     if(halfY >= p.col){
    //         if(b->node.quadrants[SE] == NULL){
    //             return NULL;
    //         }
    //         return search(b->node.quadrants[SE], p);
    //     }else{
    //         if(b->node.quadrants[NE] == NULL){
    //             return NULL;
    //         }
    //         return search(b->node.quadrants[NE], p);
    //     }
    // }
    return NULL;
}


Coordinate make_point (int x, int y){
    Coordinate c;
    c.row = x;
    c.col = y;
    return c;
}


void sumShipSizesAndSetHP(int *lstOfShips, int *p1Hp, int *p2Hp){
    for(int i=0;i<6;i++){
        switch (i)
        {
        case CARRIER:
            *p1Hp += CARRIER_SIZE * lstOfShips[i];
            *p2Hp += CARRIER_SIZE * lstOfShips[i];
            break;
        case BATTLESHIP:
            *p1Hp += BATTLESHIP_SIZE * lstOfShips[i];
            *p2Hp += BATTLESHIP_SIZE * lstOfShips[i];
            break;
        case CRUISER:
            *p1Hp += CRUSIER_SIZE * lstOfShips[i];
            *p2Hp += CRUSIER_SIZE * lstOfShips[i];
            break;
        case SUBMARINE:
            *p1Hp += SUBMARINE_SIZE * lstOfShips[i];
            *p2Hp += SUBMARINE_SIZE * lstOfShips[i];
            break;
        case DESTROYER:
            *p1Hp += DESTROYER_SIZE * lstOfShips[i];
            *p2Hp += DESTROYER_SIZE * lstOfShips[i];
            break;
        case TSHAPE:
            *p1Hp += (TSHAPE_SIZE + 2) * lstOfShips[i];
            *p2Hp += (TSHAPE_SIZE + 2) * lstOfShips[i];
            break;
        }
    }
}

void printTree(QD_NODE *b, int x, int y){
    QD_NODE *aux = NULL;
    Coordinate p;
    for(int i=0 ;i < x; i++){
		if(i <= 9){
            printf(KNRM "\t %d|",i);
        }else{
            printf(KNRM "\t%d|",i);
        }

        for(int j=0; j < y ;j++){
            p = make_point(i,j);
            aux = search(b, p);
            if(aux == NULL){
                if(j <= 9)
                    printf(KBLU "  ~  |");
                else
                    printf(KBLU "  ~  |");
            }else{
                switch(aux->node.leaf.cell.shipType){
                case GOODSHOT:
                    printf(KYEL "  X  ");
                    printf(KBLU "|");
                    break;
                case CARRIER:
                    printf(KCYN "  C  ");
                    printf(KBLU "|");
                    break;
                case BATTLESHIP:
                    printf(KCYN "  B  ");
                    printf(KBLU "|");
                    break;
                case CRUISER:
                    printf(KCYN "  R  ");
                    printf(KBLU "|");
                    break;
                case SUBMARINE:
                    printf(KCYN "  S  ");
                    printf(KBLU "|");
                    break;
                case DESTROYER:
                    printf(KCYN "  D  ");
                    printf(KBLU "|");
                    break;
                case TSHAPE:
                    printf(KCYN "  T  ");
                    printf(KBLU "|");
                    break;
                case WATERSHOT:
                    printf(KRED "  X  ");
                    printf(KBLU "|");
                    break;
                default:  
                    break;
                }
            }
        }
        printf("\n");
    }

    printf("\t   ");
	for(int k=0;k < y;k++){
		if(k <=9){
            printf(KNRM "  %d  |",k);
        }else{
            printf(KNRM "  %d |",k);
        }
	}
}