#include "shape/sshape.h"
#include "tetris.h"

CubeColor SShape::getColor(){
    return CubeColor::Green;
}

void SShape::reset(){
    /**
     *   0 1 1
     *   1 1 0
     */
    points[0] = -1;
    points[1] = 5;

    points[2] = -1;
    points[3] = 6;

    points[4] = 0;
    points[5] = 4;

    points[6] = 0;
    points[7] = 5;

    morp = Shape::MORP_ZERO;
}

void SShape::onRotate(){
    int curMorp = morp;
    do{
        std::vector<int> rotatePoints = std::vector<int>(8, 0);
        if(curMorp == Shape::MORP_ZERO){
            /**
             * 0 1 1    0 1 0
             * 1 1 0 => 0 + 1
             * 0 0 0    0 0 1 
             * 
             */
            int midRow = points[0] + 1;
            int midCol = points[1];

            rotatePoints[0] = midRow - 1;
            rotatePoints[1] = midCol;

            rotatePoints[2] = midRow;
            rotatePoints[3] = midCol;

            rotatePoints[4] = midRow;
            rotatePoints[5] = midCol + 1;

            rotatePoints[6] = midRow + 1;
            rotatePoints[7] = midCol + 1;

            curMorp = Shape::MORP_ONE;
        }else if(curMorp == Shape::MORP_ONE){
             /**
             * 0 1 0      0 1 1
             * 0 1 1  =>  1 + 0
             * 0 0 1      0 0 0
             * 
             */
            int midRow = points[0] + 1;
            int midCol = points[1];

            rotatePoints[0] = midRow - 1;
            rotatePoints[1] = midCol;

            rotatePoints[2] = midRow - 1;
            rotatePoints[3] = midCol + 1;

            rotatePoints[4] = midRow;
            rotatePoints[5] = midCol - 1;

            rotatePoints[6] = midRow;
            rotatePoints[7] = midCol;
            
            curMorp = Shape::MORP_ZERO;
        }

        if(checkPointsOverlayGrid(rotatePoints)){
            curMorp = (curMorp + 1)% 2;
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

int SShape::getShapeWidth(){
    if(game == nullptr){
        return 0;
    }

    return 3 * game->gameScene->cubeSize;
}
