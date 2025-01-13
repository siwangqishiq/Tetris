#include "shape/shape.h"

class IShape : public Shape{
public:
    virtual std::vector<int> getPoints();
    virtual CubeColor getColor();
    virtual void rotate();
};