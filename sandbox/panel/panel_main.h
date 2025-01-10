#pragma once

#include "purple.h"
#include "tetris.h"

class PanelMain{
public:
    PanelMain(TetrisGame *game,float cubeSize,
         float left , float top , float width , float height);

    void update();
    void render();
private:
    TetrisGame *game = nullptr;
    float cubeSize;
    purple::Rect rect;
};