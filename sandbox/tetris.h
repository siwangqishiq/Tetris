#pragma once

#include <memory>
#include "purple.h"
#include "scene/scene_splash.h"
#include "scene/scene_game.h"
#include <vector>
#include "common.h"

enum GameState{
    Splash = 0,
    Start = 1,

    GameOver = 10
};


const int GRID_TYPE_IDLE = 0;
const int GRID_TYPE_WALL = -1;


class TextureImage;
class TextureImageRegion;

class TetrisGame : public purple::IApp{
public:
    const static int COL_COUNT = 12; //12列
    const static int ROW_COUNT = 21; //21行

    GameState state = Splash;

    std::shared_ptr<purple::TextureImage> cubesTexture;
    std::shared_ptr<SceneSplash> splashScene = nullptr;
    std::shared_ptr<SceneGame> gameScene = nullptr;

    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;
    
    virtual bool onInputEvent(purple::InputEvent &event);

    void updateState(GameState newState);

    void exitGame();

    std::vector<std::shared_ptr<purple::TextureImageRegion>> cubesTextureList;

    std::vector<std::vector<int>> gridData;

    int getNextTetrisType();

    int genNextTertisType();

    long updateDelayMils = 1000;//更新时间间隔 
private:
    void loadResoures();

    void initGridData();

    std::string TAG = "TetrisGame";

    int nextTetris = -1;
};