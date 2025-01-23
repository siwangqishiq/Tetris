#pragma once
#include "purple.h"
#include <memory>

class TetrisGame;
class PanelMain;
class PanelNext;
class PanelScore;

const int MENU_RESUME = 0;
const int MENU_EXIT_SPLASH = 1;
const int MENU_EXIT_GAME = 2;

class SceneGame{
public:
    std::shared_ptr<PanelMain> panelMain;
    std::shared_ptr<PanelNext> panelNext;
    
    SceneGame(TetrisGame *_game):game(_game){
    }

    const static int PADDING = 10;

    float cubeSize = 0.0f; 

    void init();

    void update();

    void render();

    void dispose();

    void onInputEvent(purple::InputEvent &event);

    std::shared_ptr<PanelScore> getPanelScore(){
        return panelScore;
    }
private:
    TetrisGame *game = nullptr;

    std::shared_ptr<PanelScore> panelScore;
    
    std::vector<std::wstring> menus = {L"继续",L"退出到标题页",L"退出到桌面"};
    int menuIndex = 0;

    void pauseGame();
    void resumeGame();
    void renderGamePauseUi();

    void renderMenus();

    void onEscKeyPressed();
    void onUpKeyPressed();
    void onDownKeyPressed();
    void onEnterKeyPressed();
};