#pragma once

#include <memory>
#include "purple.h"
#include "scene/scene_splash.h"
#include "scene/scene_game.h"

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

class TextureImage;
class TextureImageRegion;

class TetrisGame : public purple::IApp{
public:
    GameState state = Splash;

    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;
    
    virtual bool onInputEvent(purple::InputEvent &event);

    void updateState(GameState newState);

    void exitGame();

    std::vector<std::shared_ptr<purple::TextureImageRegion>> cubesTextureList;
private:
    void loadResoures();

    std::string TAG = "TetrisGame";

    std::shared_ptr<purple::TextureImage> cubesTexture;
 

    std::shared_ptr<SceneSplash> splashScene = nullptr;
    std::shared_ptr<SceneGame> gameScene = nullptr;
};