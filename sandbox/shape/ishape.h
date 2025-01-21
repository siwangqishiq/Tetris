#pragma once

#include "shape/shape.h"

class TetrisGame;
class IShape : public Shape{
public:
    IShape(TetrisGame *game_):Shape(game_){
    }
    
    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();

    virtual int getShapeWidth();
    
    
    // virtual void onMoveLeft();
    // virtual void onMoveRight();
    // virtual void onMoveDown();
private:
    bool isVertical = false;
    void updateVertPoints();
    void updateHorPoints();
};