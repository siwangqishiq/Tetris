#pragma once

#include "shape/shape.h"

class JShape : public Shape{
public:
    JShape(TetrisGame *game_):Shape(game_){
    }

    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();
};