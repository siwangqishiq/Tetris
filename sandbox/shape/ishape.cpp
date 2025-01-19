#include "shape/ishape.h"
#include "shape/shape.h"
#include "tetris.h"

void IShape::reset(){
    updateHorPoints();
    isVertical = false;
    // updateVertPoints();
    // isVertical = true;
}

CubeColor IShape::getColor(){
    return CubeColor::Cyan;
}

void IShape::onRotate(){
    std::vector<int> rotatePoints = points;

    int midPointRow = rotatePoints[2 * 2];
    int midPointCol = rotatePoints[2 * 2 + 1];

    if(isVertical){//垂直形态 ->水平
        // std::cout << "hor->ver rotaet 0" << std::endl;
        rotatePoints[0*2] = midPointRow;
        rotatePoints[0*2 + 1] = midPointCol - 2;

        // std::cout << "hor->ver rotaet 1" << std::endl;
        rotatePoints[1*2] = midPointRow;
        rotatePoints[1*2 + 1] = midPointCol - 1;

        // std::cout << "hor->ver rotaet 3" << std::endl;
        rotatePoints[3*2] = midPointRow;
        rotatePoints[3*2 + 1] = midPointCol + 1;
    }else{//水平形态 -> 垂直
        // std::cout << "hor->ver rotaet end" << std::endl;

        // std::cout << "ver->hor rotaet 0" << std::endl;
        rotatePoints[0*2] = midPointRow - 2;
        rotatePoints[0*2 + 1] = midPointCol;

        // std::cout << "ver->hor rotaet 1" << std::endl;
        rotatePoints[1*2] = midPointRow - 1;
        rotatePoints[1*2 + 1] = midPointCol;
        
        // std::cout << "ver->hor rotaet 3" << std::endl;
        rotatePoints[3*2] = midPointRow + 1;
        rotatePoints[3*2 + 1] = midPointCol;

        // std::cout << "ver->hor rotaet 0" << std::endl;
    }

    if(checkPointsOverlayGrid(rotatePoints)){
        std::cout << "point overlay grid data" << std::endl;
        return;
    }

    points = rotatePoints;
    isVertical = !isVertical;
}

// void IShape::onMoveLeft(){
//     if(!checkAllCubesCanMoveLeft()){
//         return;
//     }

//     const int len = points.size() >> 1;
//     for(int i = 0 ; i < len ; i++){
//         int col = points[(i << 1) + 1];
//         points[(i << 1) + 1] = col - 1;
//     }//end for i
// }

// void IShape::onMoveRight(){
//     if(!checkAllCubesCanMoveRight()){
//         return;
//     }

//     const int len = points.size() >> 1;
//     for(int i = 0 ; i < len ; i++){
//         int col = points[ (i << 1) + 1];
//         points[(i << 1) + 1] = col + 1;
//     }//end for i
// }

// void IShape::onMoveDown(){
//     if(!checkAllCubesCanMoveDown()){
//         return;
//     }

//     const int len = points.size() >> 1;
//     for(int i = 0 ; i < len ; i++){
//         int row = points[(i << 1)];
//         points[(i << 1)] = row + 1;
//     }//end for i
// }

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
    points[1] = 3;

    points[2] = 0;
    points[3] = 4;

    points[4] = 0;
    points[5] = 5;

    points[6] = 0;
    points[7] = 6;
}

