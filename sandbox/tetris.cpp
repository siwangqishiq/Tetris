#include "tetris.h"
#include "purple.h"
#include "purple_ui.h"
#include "input/input_manager.h"
#include "render/sprite.h"
#include "tetris.h"
#include "utils.h"

extern bool isAppExist;//外部全局变量 控制退出app

TetrisGame::~TetrisGame(){
    purple::Log::i("TetrisGame", "~TetrisGame");
}

void TetrisGame::onInit(){
    splashScene = std::make_shared<SceneSplash>(this);
    gameScene = std::make_shared<SceneGame>(this);

    splashScene->init();
    gameScene->init();
    purple::InputManager::getInstance()->addEventListener("input" , [this](purple::InputEvent &event){
        return this->onInputEvent(event);
    });
    
    loadResoures();

    initGridData();
    
    state = GameState::Start;
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
            gameScene->onInputEvent(event);
            break;
        default:
            break;
    }//end switch
    return false;
}

int TetrisGame::getNextTetrisType(){
    if(nextTetris < 0){
        return genNextTertisType();
    }
    
    return nextTetris;
}

int TetrisGame::genNextTertisType(){
    return purple::RndInt(TETRIS_TYPE_I , TETRIS_TYPE_Z);
}

void TetrisGame::onDispose(){
    purple::InputManager::getInstance()->clearCallback();
    if(splashScene != nullptr){
        splashScene->dispose();
    }
}


