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

    void update(float left , float top , float cubeSize);
    
    virtual CubeColor getColor();

    virtual glm::vec4 getShaodowColor();
    
    virtual void reset();
    virtual void render();
    virtual void renderShadow();
    
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

    virtual int getShapeWidth();

    bool checkAllCubesCanMoveLeft();
    bool checkAllCubesCanMoveRight();
    bool checkAllCubesCanMoveDown();

    int findShadowShapeRowOffset();

    bool checkPointsOverlayGrid(std::vector<int> &inputPoints);

    static bool checkRowColInRange(int row , int col);
    
    virtual ~Shape();

    std::vector<int>& getPoints();

    void setPoints(std::vector<int> newPoints){
        this->points = newPoints;
    }
protected:
    std::vector<int> points = {0,0, 0,0, 0,0, 0,0}; //行 ,列
    TetrisGame *game = nullptr;

    int morp = MORP_ZERO;

    float left;
    float top;
    float cubeSize;
};

