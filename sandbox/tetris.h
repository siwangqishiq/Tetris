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
};


const int GRID_TYPE_IDLE = 0;
const int GRID_TYPE_WALL = 100;


class TextureImage;
class TextureImageRegion;
class AudioEntity;

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

    std::vector<std::vector<int>> gridData;

    int getNextTetrisType();

    int genNextTertisType();

    int getNextTetrisValue(){
        return nextTetris;
    }

    std::shared_ptr<purple::TextureImageRegion> getCubeImageRegionByColor(int cubeColor);

    virtual ~TetrisGame();

    long updateDelayMils = 1000;//更新时间间隔 
    long deltaTimeMils = -1;

    std::shared_ptr<purple::AudioEntity> audioBgm;
    std::shared_ptr<purple::AudioEntity> audioFailed;
    std::shared_ptr<purple::AudioEntity> audioCubeMove;
    std::shared_ptr<purple::AudioEntity> audioCubeRotate;
    std::shared_ptr<purple::AudioEntity> audioCubeDismiss;

    void playSound(std::shared_ptr<purple::AudioEntity> entity);

    void stopSound(std::shared_ptr<purple::AudioEntity> entity);
private:
    void loadResoures();

    void initGridData();

    std::string TAG = "TetrisGame";

    std::vector<std::shared_ptr<purple::TextureImageRegion>> cubesTextureList;

    int nextTetris = -1;

    void updateTime();

    long priorFrameTimeMils = 0;
};