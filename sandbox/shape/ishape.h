#include "shape/shape.h"

class IShape : public Shape{
public:
    IShape();
    
    virtual CubeColor getColor();
    virtual void rotate();

private:
    bool isVertical = false;
    void updateVertPoints();
    void updateHorPoints();
};