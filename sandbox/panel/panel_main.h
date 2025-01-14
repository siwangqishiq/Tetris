#pragma once

#include "purple.h"
#include "tetris.h"
#include <vector>
#include <memory>
#include "shape/shape.h"

enum PanelMainState{
    UNSET = -1,
    GenCube = 1, //生成cube
    CubeDown = 2, // 方块下降
    CubeDismiss = 3,//方块消失
};

class PanelMain{
public:
    PanelMain(TetrisGame *game,float cubeSize,
         float left , float top , float width , float height);

    void update();
    void render();
    void onInputEvent(purple::InputEvent &event);

    void genNewCube();

    std::shared_ptr<Shape> createShapeByType(int shapeType);
private:
    TetrisGame *game = nullptr;
    float cubeSize;
    purple::Rect rect;

    PanelMainState state = UNSET;

    std::shared_ptr<Shape> currentShape = nullptr;

    std::vector<int> holderPoints ={-1,-1,-1,-1,-1,-1,-1,-1};

    void currentTetrisDown();//方块下降

    void blitCubeToGridData();
    void clearCubeGridData();

    void putGridData(std::vector<int> &points, int value);
};