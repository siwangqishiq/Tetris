#include "shape/shape.h"

class LShape : public Shape{
public:
    LShape(TetrisGame *game_):Shape(game_){
    }

    virtual CubeColor getColor();

    virtual void reset();
    virtual void onRotate();
};