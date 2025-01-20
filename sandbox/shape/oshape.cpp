#include "shape/oshape.h"

CubeColor OShape::getColor(){
    return CubeColor::Yellow;
}

void OShape::reset(){
    points[0] = -1;
    points[1] = 4;

    points[2] = -1;
    points[3] = 5;

    points[4] = 0;
    points[5] = 4;

    points[6] = 0;
    points[7] = 5;

    morp = Shape::MORP_ZERO;
}

void OShape::onRotate(){
    //do nothing
    
    // int curMorp = morp;
    // if(curMorp == Shape::MORP_ZERO){
    //     curMorp = Shape::MORP_ONE;
    // }else if(curMorp == Shape::MORP_ONE){
    //     curMorp = Shape::MORP_TWO;
    // }else if(curMorp == Shape::MORP_TWO){
    //     curMorp = Shape::MORP_THREE;
    // }else if(curMorp == Shape::MORP_THREE){
    //     curMorp = Shape::MORP_ZERO;
    // }
}