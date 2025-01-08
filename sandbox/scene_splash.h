#pragma once

#include "purple.h"

class TetrisGame;
class SceneSplash{
public:
    SceneSplash(TetrisGame *_game):game(_game){
    }

    void init();

    void update();

    void render();
private:
    TetrisGame *game;
};