#pragma once
#include "purple.h"

class TetrisGame;
class SceneGame{
public:
    SceneGame(TetrisGame *_game):game(_game){
    }

    void init();

    void update();

    void render();
private:
    TetrisGame *game;
};