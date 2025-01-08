#pragma once

#include "purple.h"
#include <vector>
#include <string>

class TetrisGame;
class TextureImage;

class SceneSplash{
public:
    SceneSplash(TetrisGame *_game):game(_game){
    }

    void init();

    void update();

    void render();
private:
    TetrisGame *game;

    std::shared_ptr<purple::TextureImage> logoImage;

    float logoTop;
    float logoLeft;
    float logoWidth;
    float logoHeight;

    glm::vec4 ColorTextSelected = glm::vec4(1.0f , 1.0f , 1.0f , 1.0f);
    glm::vec4 ColorTextUnselected = glm::vec4(1.0f , 1.0f , 1.0f , 0.3f);

    std::vector<std::wstring> menuNames = {L"新游戏",L"退出"};
    int currentMenuIndex = 0;
};