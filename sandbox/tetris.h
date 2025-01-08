#pragma once

#include <memory>
#include "purple.h"

enum GameState{
    Splash = 0,
    GameStart = 1,
    GameOver = 10
};


class TetrisGame : public purple::IApp{
public:
    GameState state = Splash;

    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;
    
private:
    std::string TAG = "TetrisGame";
};