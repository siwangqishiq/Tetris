#include "tetris.h"
#include "purple.h"
#include "purple_ui.h"
#include "input/input_manager.h"
#include "render/sprite.h"
#include "tetris.h"
#include "utils.h"
#include "widget/random_util.h"

extern bool isAppExist;//外部全局变量 控制退出app

TetrisGame::~TetrisGame(){
    purple::Log::i("TetrisGame", "~TetrisGame");
}

void TetrisGame::onInit(){
    purple::RandomUtil::setRandomSeed(purple::currentTimeMillis() / 1000);

    splashScene = std::make_shared<SceneSplash>(this);
    gameScene = std::make_shared<SceneGame>(this);

    splashScene->init();
    gameScene->init();
    purple::InputManager::getInstance()->addEventListener("input" , [this](purple::InputEvent &event){
        return this->onInputEvent(event);
    });
    
    loadResoures();

    initGridData();
    
    state = GameState::Splash;
    priorFrameTimeMils = purple::currentTimeMillis();
}

void TetrisGame::updateTime(){
    long currentTime = purple::currentTimeMillis();
    deltaTimeMils =  currentTime - priorFrameTimeMils;
    priorFrameTimeMils = currentTime;
}

void TetrisGame::loadResoures(){
    purple::Engine::getRenderEngine()->loadTextFontRes("youyuan","text/youyuan.ttf", true);

    cubesTexture = purple::BuildImageByAsset("img/cubes.png");

    const int size = 64;
    for(int i = 0 ; i < CubeColor::End; i++){
        std::shared_ptr<purple::TextureImageRegion> textureRegion = cubesTexture->createImageRegion(i * size, size, size, size);
        cubesTextureList.push_back(textureRegion);
    }//end for i


    audioItemChange = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/menu_item_change.wav");
    audioBgm = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/bgm3.mp3" , true);
    audioFailed = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/failed.mp3");
    audioCubeMove = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/cube_down.wav");
    audioCubeRotate = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/cube_rotate.wav");
    audioCubeDismiss = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/cube_dismiss.wav");
}

void TetrisGame::playSound(std::shared_ptr<purple::AudioEntity> entity){
    if(entity == nullptr){
        return;
    }
    purple::AudioManager::getInstance()->playAudioEntity(entity);
}

void TetrisGame::stopSound(std::shared_ptr<purple::AudioEntity> entity){
    if(entity == nullptr){
        return;
    }
    purple::AudioManager::getInstance()->stopAudioEntity(entity);
}

void TetrisGame::replaySound(std::shared_ptr<purple::AudioEntity> entity){
    if(entity == nullptr){
        return;
    }
    purple::AudioManager::getInstance()->restartAudioEntity(entity);
}

std::shared_ptr<purple::TextureImageRegion> TetrisGame::getCubeImageRegionByColor(int cubeColor){
    int colorIndex = cubeColor - 1;
    const int textureListLen = static_cast<int>(cubesTextureList.size());
    if(colorIndex < 0 || colorIndex >= textureListLen){
        return cubesTextureList[0];
    }
    return cubesTextureList[colorIndex];
}

void TetrisGame::initGridData(){
    for(int i = 0; i < ROW_COUNT ;i++){
        std::vector<int> rowVec;
        for(int j = 0; j < COL_COUNT ; j++){
            rowVec.push_back(GRID_TYPE_IDLE);
        }//end for j
        gridData.push_back(rowVec);
    }//end for i

    //set wall
    for(int i = 0; i < COL_COUNT ; i++){
        gridData[ROW_COUNT - 1][i] = GRID_TYPE_WALL;
    }

    for(int i = 0; i < ROW_COUNT ; i++){
        gridData[i][0] = GRID_TYPE_WALL;
        gridData[i][COL_COUNT - 1] = GRID_TYPE_WALL;
    }
}

void TetrisGame::onTick(){
    updateTime();
    switch(state){
        case Splash:
            splashScene->update();
            splashScene->render();
            break;
        case Start:
        case Pause:
            gameScene->update();
            gameScene->render();
            break;
        default:
            break;
    }//end switch
}

void TetrisGame::updateState(GameState newState){
    if(state != newState){
        state = newState;
    }
}

void TetrisGame::exitGame(){
    isAppExist = true;
}

bool TetrisGame::onInputEvent(purple::InputEvent &event){
    switch(state){
        case Splash:
            splashScene->onInputEvent(event);
            break;
        case Start:
        case Pause:
            gameScene->onInputEvent(event);
            break;
        default:
            break;
    }//end switch
    return false;
}

int TetrisGame::getNextTetrisType(){
    if(nextTetris < 0){
        return purple::RndInt(TETRIS_TYPE_I , TETRIS_TYPE_Z);
    }
    return nextTetris;
}

int TetrisGame::genNextTertisType(){
    nextTetris = purple::RndInt(TETRIS_TYPE_I , TETRIS_TYPE_Z);
    // nextTetris = TETRIS_TYPE_I;//debug
    return nextTetris;
}

void TetrisGame::onDispose(){
    purple::InputManager::getInstance()->clearCallback();
    if(splashScene != nullptr){
        splashScene->dispose();
    }
    
    purple::AudioManager::getInstance()->releaseAudioEntity(audioBgm);
    purple::AudioManager::getInstance()->releaseAudioEntity(audioFailed);
    purple::AudioManager::getInstance()->releaseAudioEntity(audioCubeMove);
    purple::AudioManager::getInstance()->releaseAudioEntity(audioCubeRotate);
    purple::AudioManager::getInstance()->releaseAudioEntity(audioCubeDismiss);
    purple::AudioManager::getInstance()->releaseAudioEntity(audioItemChange);
}


