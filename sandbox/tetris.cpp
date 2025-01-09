#include "tetris.h"
#include "purple.h"
#include "purple_ui.h"
#include "input/input_manager.h"

extern bool isAppExist;//外部全局变量 控制退出app

void TetrisGame::onInit(){
    splashScene = std::make_shared<SceneSplash>(this);
    gameScene = std::make_shared<SceneGame>(this);


    splashScene->init();
    gameScene->init();
    purple::InputManager::getInstance()->addEventListener("input" , [this](purple::InputEvent &event){
        return this->onInputEvent(event);
    });
    
    state = Splash;
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


