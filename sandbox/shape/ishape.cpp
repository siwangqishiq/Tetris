#include "shape/ishape.h"

IShape::IShape(){
    updateHorPoints();
    isVertical = false;
}

void IShape::reset(){
    dx = 2;
    dy = 0;
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

void IShape::updateVertPoints(){
    points[0] = 0;
    points[1] = 0;

    points[2] = 1;
    points[3] = 0;

    points[4] = 2;
    points[5] = 0;

    points[6] = 3;
    points[7] = 0;
}

void IShape::updateHorPoints(){
    points[0] = 0;
    points[1] = 0;

    points[2] = 0;
    points[3] = 1;

    points[4] = 0;
    points[5] = 2;

    points[6] = 0;
    points[7] = 3;
}

