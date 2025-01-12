#pragma once

#include <memory>
#include "purple.h"
#include "scene/scene_splash.h"
#include "scene/scene_game.h"
#include <vector>

enum GameState{
    Splash = 0,
    Start = 1,
    GameOver = 10
};

enum CubeColor{
    Yellow = 0,
    Cyan = 1,
    Red = 2,
    Blue = 3,
    Green = 4,
    Orange = 5,
    Purple = 6,
    Gray = 7,
    End = 8
};


const int GRID_TYPE_IDLE = 0;
const int GRID_TYPE_WALL = 10;


class TextureImage;
class TextureImageRegion;

class TetrisGame : public purple::IApp{
public:
    const static int COL_COUNT = 12; //12列
    const static int ROW_COUNT = 22; //22行


    GameState state = Splash;

    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;
    
    virtual bool onInputEvent(purple::InputEvent &event);

    void updateState(GameState newState);

    void exitGame();

    std::vector<std::shared_ptr<purple::TextureImageRegion>> cubesTextureList;

    std::vector<std::vector<int>> gridData;
private:
    void loadResoures();

    void initGridData();

    std::string TAG = "TetrisGame";

    std::shared_ptr<purple::TextureImage> cubesTexture;
 
    std::shared_ptr<SceneSplash> splashScene = nullptr;
    std::shared_ptr<SceneGame> gameScene = nullptr;
};