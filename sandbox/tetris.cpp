#include "tetris.h"
#include "purple.h"
#include "purple_ui.h"

void TetrisGame::onInit(){
    splashScene = std::make_shared<SceneSplash>(this);
    gameScene = std::make_shared<SceneGame>(this);


    splashScene->init();
    gameScene->init();

    state = Start;
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

void TetrisGame::onDispose(){

}


