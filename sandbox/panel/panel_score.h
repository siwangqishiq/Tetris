#pragma once
#include "purple.h"

class TetrisGame;

class PanelScore{
public:
    PanelScore(TetrisGame *game, float fontSize, float left,float top, float width);

    void update();

    void render();

    void addScore(int addScore);

    void resetScore();
private:
    TetrisGame *game = nullptr;
    float left;
    float width;
    float top;
    float fontSize;

    int score = 0;
    int targerScore = 0;
};