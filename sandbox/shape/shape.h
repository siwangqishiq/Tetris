#pragma once

#include <vector>
#include "common.h"

class TetrisGame;

class Shape{
public:
    Shape(TetrisGame *game);
    
    virtual CubeColor getColor();
    virtual void rotate();
    virtual void reset();
    virtual void render();
    
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveDown();
    virtual void moveUp();
    
    virtual ~Shape();

    std::vector<int>& getPoints();
protected:
    std::vector<int> points = {0,0, 0,0, 0,0, 0,0}; //行 ,列
    TetrisGame *game = nullptr;
private:
};

