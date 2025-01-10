#include "tetris.h"
#include "purple.h"
#include "purple_ui.h"
#include "input/input_manager.h"
#include "render/sprite.h"

extern bool isAppExist;//外部全局变量 控制退出app

void TetrisGame::onInit(){
    splashScene = std::make_shared<SceneSplash>(this);
    gameScene = std::make_shared<SceneGame>(this);

    splashScene->init();
    gameScene->init();
    purple::InputManager::getInstance()->addEventListener("input" , [this](purple::InputEvent &event){
        return this->onInputEvent(event);
    });
    
    loadResoures();

    state = Start;
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

void TetrisGame::onTick(){
    switch(state){
        case Splash:
            splashScene->update();
            splashScene->render();
            break;
        case Start:
            gameScene->update();
            gameScene->render();
            break;
        case GameOver:
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
            break;
        case GameOver:
            break;
        default:
            break;
    }//end switch
    return false;
}

void TetrisGame::onDispose(){
    purple::InputManager::getInstance()->clearCallback();
    if(splashScene != nullptr){
        splashScene->dispose();
    }
}


