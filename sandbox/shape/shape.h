#pragma once

#include <vector>
#include "common.h"

class TetrisGame;

class Shape{
public:
    static const int MORP_ZERO = 0;
    static const int MORP_ONE = 1;
    static const int MORP_TWO = 2;
    static const int MORP_THREE = 3;//

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

    bool checkAllCubesCanMoveLeft();
    bool checkAllCubesCanMoveRight();
    bool checkAllCubesCanMoveDown();

    bool checkPointsOverlayGrid(std::vector<int> &inputPoints);

    static bool checkRowColInRange(int row , int col);
    
    virtual ~Shape();

    std::vector<int>& getPoints();
protected:
    std::vector<int> points = {0,0, 0,0, 0,0, 0,0}; //行 ,列
    TetrisGame *game = nullptr;

    int morp = MORP_ZERO;
};

