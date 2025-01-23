#pragma once

#include "purple.h"
#include <vector>
#include <string>

class TetrisGame;
class TextureImage;
class AudioEntity;

class SceneSplash{
public:
    SceneSplash(TetrisGame *_game):game(_game){
    }

    const static int MENU_START_GAME = 0;
    const static int MENU_EXIT_GAME = 1;

    void init();

    void update();

    void render();

    void dispose();

    void onInputEvent(purple::InputEvent &event);
private:
    TetrisGame *game;

    std::shared_ptr<purple::TextureImage> logoImage;

    float logoTop;
    float logoLeft;
    float logoWidth;
    float logoHeight;

    std::vector<std::wstring> menuNames = {L"新游戏",L"退出"};
    int currentMenuIndex = 0;

    void pressEnterKey();
    void selectNextMenuItem();
    void selectPriorMenuItem();
};