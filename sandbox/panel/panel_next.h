#pragma once

#include "purple.h"

class TetrisGame;
class PanelNext{
public:
    PanelNext(TetrisGame *game_);

    void update();
    void render();
private:
    TetrisGame *game = nullptr;

    float left = 0.0f;
    float top = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
};