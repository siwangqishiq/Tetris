#include "shape/lshape.h"
#include "tetris.h"

/**
 * 
 *  0 0 0      1 0 0      0 0 0      0 1 1
 *  1 1 1      1 0 0      0 0 1      0 0 1
 *  1 0 0      1 1 0      1 1 1      0 0 1
 * 
 *  0 0 0      0 1 0      0 0 0      1 1 0     
 *  1 0 0      0 1 0      1 1 1      1 0 0     
 *  1 1 1      1 1 0      0 0 1      1 0 0     
 * 
 */

CubeColor LShape::getColor(){
    return CubeColor::Orange;
}

void LShape::reset(){
    points[0] = -1;
    points[1] = 4;

    points[2] = -1;
    points[3] = 5;

    points[4] = -1;
    points[5] = 6;

    points[6] = 0;
    points[7] = 4;

    morp = Shape::MORP_ZERO;
}

void LShape::onRotate(){
    int curMorp = morp;
    do{
        std::vector<int> rotatePoints = std::vector<int>(8, 0);
        if(curMorp == Shape::MORP_ZERO){
            /**
             * 0 0 0    1 0 0
             * 1 1 1 => 1 0 0
             * 1 0 0    1 1 0 
             * 
             */
            int midRow = points[0];
            int midCol = points[1] + 1;

            rotatePoints[0] = midRow - 1;
            rotatePoints[1] = midCol - 1;

            rotatePoints[2] = midRow;
            rotatePoints[3] = midCol - 1;

            rotatePoints[4] = midRow + 1;
            rotatePoints[5] = midCol - 1;

            rotatePoints[6] = midRow + 1;
            rotatePoints[7] = midCol;

            curMorp = Shape::MORP_ONE;
        }else if(curMorp == Shape::MORP_ONE){
             /**
             * 1 0 0    0 0 0
             * 1 0 0 => 0 0 1
             * 1 1 0    1 1 1
             * 
             */
            int midRow = points[0] + 1;
            int midCol = points[1] + 1;

            rotatePoints[0] = midRow;
            rotatePoints[1] = midCol + 1;

            rotatePoints[2] = midRow + 1;
            rotatePoints[3] = midCol - 1;

            rotatePoints[4] = midRow + 1;
            rotatePoints[5] = midCol;

            rotatePoints[6] = midRow + 1;
            rotatePoints[7] = midCol + 1;
            
            curMorp = Shape::MORP_TWO;
        }else if(curMorp == Shape::MORP_TWO){

            /**
             * 0 0 0     0 1 1
             * 0 0 1  => 0 0 1 
             * 1 1 1     0 0 1
             * 
             */
            int midRow = points[0];
            int midCol = points[1] - 1;

            rotatePoints[0] = midRow - 1;
            rotatePoints[1] = midCol;

            rotatePoints[2] = midRow - 1;
            rotatePoints[3] = midCol + 1;
            
            rotatePoints[4] = midRow;
            rotatePoints[5] = midCol + 1;
            
            rotatePoints[6] = midRow + 1;
            rotatePoints[7] = midCol + 1;

            curMorp = Shape::MORP_THREE;
        }else if(curMorp == Shape::MORP_THREE){
            /**
             * 0 1 1     1 1 1
             * 0 0 1  => 1 0 0
             * 0 0 1     0 0 0 
             */
            int midRow = points[0] + 1;
            int midCol = points[1];

            rotatePoints[0] = midRow - 1;
            rotatePoints[1] = midCol - 1;

            rotatePoints[2] = midRow - 1;
            rotatePoints[3] = midCol;
            
            rotatePoints[4] = midRow - 1;
            rotatePoints[5] = midCol + 1;
            
            rotatePoints[6] = midRow;
            rotatePoints[7] = midCol - 1;

            curMorp = Shape::MORP_ZERO;
        }

        if(checkPointsOverlayGrid(rotatePoints)){
            curMorp = (curMorp + 1)% 4;
            if(curMorp == this->morp){
                break;
            }
        }else{
            morp = curMorp;
            points = rotatePoints;
            break;
        }
    }while(true);
}

int LShape::getShapeWidth(){
    if(game == nullptr){
        return 0;
    }

    return 3 * game->gameScene->cubeSize;
}

