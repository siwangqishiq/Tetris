#pragma once

#include "shape/shape.h"

class SShape : public Shape{
public:
    SShape(TetrisGame *game_):Shape(game_){
    }

    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();

    virtual int getShapeWidth();
};