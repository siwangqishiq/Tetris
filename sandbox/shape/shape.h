#pragma once

#include <vector>
#include "common.h"

class Shape{
public:
    Shape();

    virtual std::vector<int> getPoints() = 0;
    virtual CubeColor getColor() = 0;
    virtual void rotate() = 0;
    virtual void reset();

    virtual ~Shape();
protected:
    int dx;
    int dy;

    std::vector<int> points = {0,0,0,0,0,0,0,0};
};

