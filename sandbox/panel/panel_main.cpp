
#include "panel_main.h"
#include "purple_ui.h"

PanelMain::PanelMain(TetrisGame *game,
    float cubeSize,
    float left , float top , float width , float height){
    
    this->game = game;
    this->cubeSize = cubeSize;

    rect.left = left;
    rect.top = top;
    rect.width = width;
    rect.height = height;
}

void PanelMain::update(){

}

void PanelMain::render(){
    auto shapeBatch = purple::Engine::getRenderEngine()->getShapeBatch();
    shapeBatch->begin();
    purple::Paint paint;
    paint.color = purple::ConverColorValue(purple::Color::Yellow);
    shapeBatch->renderRect(rect , paint);
    shapeBatch->end();
}

