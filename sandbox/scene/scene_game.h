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

    float cubeSize = 0.0f; 
    
    float mainPanelWidth = 0.0f;//主游戏区域宽度

    const static int PADDING = 10;

    const static int COL_COUNT = 12; //12列
    const static int ROW_COUNT = 22; //22行
};