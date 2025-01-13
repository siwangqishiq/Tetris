#pragma once

#include "purple.h"
#include "tetris.h"
#include <vector>
#include <memory>
#include "shape/shape.h"

class PanelMain{
public:
    PanelMain(TetrisGame *game,float cubeSize,
         float left , float top , float width , float height);

    void initPos();
    void update();
    void render();

    std::shared_ptr<Shape> createShapeByType(int shapeType);
private:
    TetrisGame *game = nullptr;
    float cubeSize;
    purple::Rect rect;

    std::shared_ptr<Shape> currentShape = nullptr;

    void currentTetrisDown();//方块下降
};