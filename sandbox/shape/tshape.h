#pragma once

#include "shape/shape.h"

class TShape : public Shape{
public:
    TShape(TetrisGame *game_):Shape(game_){
    }

    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();

    virtual int getShapeWidth();
};