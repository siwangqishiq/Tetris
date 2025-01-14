#pragma once
#include "purple.h"
#include <memory>

class TetrisGame;
class PanelMain;
class PanelNext;
class PanelScore;

class SceneGame{
public:
    SceneGame(TetrisGame *_game):game(_game){
    }

    const static int PADDING = 10;

    void init();

    void update();

    void render();

    void dispose();

    void onInputEvent(purple::InputEvent &event);
private:
    TetrisGame *game = nullptr;

    float cubeSize = 0.0f; 

    std::shared_ptr<PanelMain> panelMain;
    std::shared_ptr<PanelScore> panelScore;
    std::shared_ptr<PanelNext> panelNext;
};