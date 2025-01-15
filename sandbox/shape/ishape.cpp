#include "shape/ishape.h"
#include "shape/shape.h"
#include "tetris.h"

void IShape::reset(){
}

CubeColor IShape::getColor(){
    return CubeColor::Cyan;
}

void IShape::rotate(){
    isVertical = !isVertical;
    if(isVertical){
        updateVertPoints();
    }else{
        updateHorPoints();
    }
}

void IShape::moveLeft(){
    const int len = points.size() / 2;
    for(int i = 0 ; i < len ; i++){
        int col = points[2 * i + 1];
        points[2 * i + 1] = col - 1;
    }//end for i
}

void IShape::moveRight(){
    const int len = points.size() / 2;
    for(int i = 0 ; i < len ; i++){
        int col = points[2 * i + 1];
        points[2 * i + 1] = col + 1;
    }//end for i
}

void IShape::moveDown(){
    const int len = points.size() / 2;
    for(int i = 0 ; i < len ; i++){
        int row = points[2 * i];
        points[2 * i] = row + 1;
    }//end for i
}

void IShape::updateVertPoints(){
    points[0] = 0;
    points[1] = 1;

    points[2] = -1;
    points[3] = 1;

    points[4] = -2;
    points[5] = 1;

    points[6] = -3;
    points[7] = 1;
}

void IShape::updateHorPoints(){
    points[0] = 0;
    points[1] = 1;

    points[2] = 0;
    points[3] = 2;

    points[4] = 0;
    points[5] = 3;

    points[6] = 0;
    points[7] = 4;
}

