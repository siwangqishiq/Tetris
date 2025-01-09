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


class TetrisGame : public purple::IApp{
public:
    GameState state = Splash;

    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;
    
    virtual bool onInputEvent(purple::InputEvent &event);

    void updateState(GameState newState);

    void exitGame();
private:
    std::string TAG = "TetrisGame";

    std::shared_ptr<SceneSplash> splashScene = nullptr;
    std::shared_ptr<SceneGame> gameScene = nullptr;
};