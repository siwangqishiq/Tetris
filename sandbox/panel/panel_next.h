#pragma once

#include "purple.h"
#include <memory>

class TetrisGame;
class Shape;
class PanelNext{
public:
    PanelNext(TetrisGame *game_);

    void update();
    void render();

    void nextTetrisChanged(int newNext);
private:
    int nextTetrisType = -1;

    TetrisGame *game = nullptr;

    float left = 0.0f;
    float top = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    std::shared_ptr<Shape> nextShape = nullptr;
    
    void adjustShapePoints();
};