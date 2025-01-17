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
    Blit = 3,// 下降结束 同步数据到grid
    GameOver = 9,//游戏结束
    CubeDismiss = 10,//方块消失
};

class PanelMain{
public:
    PanelMain(TetrisGame *game,float cubeSize,
         float left , float top , float width , float height);

    void update();
    void render();
    void onInputEvent(purple::InputEvent &event);

    void genNewCube();

    void blitTetrisToGrid();

    std::shared_ptr<Shape> createShapeByType(int shapeType);
    purple::Rect rect;

    void onGameOver();
private:
    TetrisGame *game = nullptr;
    float cubeSize;

    PanelMainState state = UNSET;

    long timeRecord = 0;

    std::shared_ptr<Shape> currentShape = nullptr;

    std::vector<int> willDismissRows; //待消失行

    void currentTetrisDown();//方块下降
    
    void renderGrids();

    void checkDismissGrid();

    void dismissGridRows();

    void checkIsGameOver();
};