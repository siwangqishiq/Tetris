#pragma once

#include <vector>
#include "common.h"

class TetrisGame;

class Shape{
public:
    Shape(TetrisGame *game);
    
    virtual CubeColor getColor();
    
    virtual void reset();
    virtual void render();
    
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();

    virtual void onRotate();
    virtual void onMoveLeft();
    virtual void onMoveRight();
    virtual void onMoveUp();
    virtual void onMoveDown();
    
    virtual ~Shape();

    std::vector<int>& getPoints();
protected:
    std::vector<int> points = {0,0, 0,0, 0,0, 0,0}; //行 ,列
    TetrisGame *game = nullptr;
private:
};

