#pragma once

#include "shape/shape.h"

class OShape : public Shape{
public:
    OShape(TetrisGame *game_):Shape(game_){
    }

    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();
};