#pragma once

#include "shape/shape.h"

class ZShape : public Shape{
public:
    ZShape(TetrisGame *game_):Shape(game_){
    }
    
    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();
    virtual int getShapeWidth();
};