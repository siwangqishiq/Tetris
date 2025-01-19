#include "shape/lshape.h"

CubeColor LShape::getColor(){
    return CubeColor::Orange;
}

void LShape::reset(){
    points[0] = -1;
    points[1] = 4;

    points[2] = 0;
    points[3] = 4;

    points[4] = 0;
    points[5] = 5;

    points[6] = 0;
    points[7] = 6;

    morp = Shape::MORP_ZERO;
}

/**        + +            +
 *  +      +    + + +     + 
 *  + + +  +        +   + + 
 */
void LShape::onRotate(){
    
    int curMorp = morp;

    std::vector<int> rotatePoints = points;
    if(curMorp == Shape::MORP_ZERO){
        int midRow = points[0];
        int midCol = points[1];

        rotatePoints[0] = midRow - 1;
        rotatePoints[1] = midCol;

        rotatePoints[2] = midRow - 1;
        rotatePoints[3] = midCol + 1;

        rotatePoints[4] = midRow;
        rotatePoints[5] = midCol;

        rotatePoints[4] = midRow + 1;
        rotatePoints[5] = midCol;

        curMorp = Shape::MORP_ONE;
    }else if(curMorp == Shape::MORP_ONE){
        int midRow = points[4];
        int midCol = points[5];

        rotatePoints[0] = midRow;
        rotatePoints[1] = midCol;

        rotatePoints[2] = midRow - 1;
        rotatePoints[3] = midCol + 1;

        rotatePoints[4] = midRow;
        rotatePoints[5] = midCol;

        rotatePoints[4] = midRow + 1;
        rotatePoints[5] = midCol;

        curMorp = Shape::MORP_TWO;
    }else if(curMorp == Shape::MORP_TWO){
        
        curMorp = Shape::MORP_THREE;
    }else if(curMorp == Shape::MORP_THREE){

        curMorp = Shape::MORP_ZERO;
    }


}
