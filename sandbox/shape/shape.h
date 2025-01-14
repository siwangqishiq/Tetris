#pragma once

#include <vector>
#include "common.h"

class Shape{
public:
    Shape();

    
    virtual CubeColor getColor() = 0;
    virtual void rotate() = 0;

    virtual void reset();
    virtual std::vector<int> getPoints();

    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveDown();
    
    virtual ~Shape();
protected:
    int dy = 0; //行偏移
    int dx = 0; //列偏移

    std::vector<int> points = {0,0,0,0,0,0,0,0};
};

