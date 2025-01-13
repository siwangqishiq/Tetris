#pragma once

#include "purple.h"
#include "tetris.h"
#include <vector>


class PanelMain{
public:
    PanelMain(TetrisGame *game,float cubeSize,
         float left , float top , float width , float height);

    void initPos();
    void update();
    void render();
private:
    TetrisGame *game = nullptr;
    float cubeSize;
    purple::Rect rect;

    const int TETRIS_DATA_COUNT = 4;
    int curTetrisType = -1;
    std::vector<std::pair<int,int>> tetrisPos;
};