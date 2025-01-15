#include "shape/shape.h"

class TetrisGame;
class IShape : public Shape{
public:
    IShape(TetrisGame *game_):Shape(game_){
        // updateHorPoints();
        updateVertPoints();
        isVertical = false;
    }
    
    virtual CubeColor getColor();
    virtual void rotate();
    virtual void reset();

    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveDown();

private:
    bool isVertical = false;
    void updateVertPoints();
    void updateHorPoints();
};