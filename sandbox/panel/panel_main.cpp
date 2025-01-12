
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
    // auto shapeBatch = purple::Engine::getRenderEngine()->getShapeBatch();
    // shapeBatch->begin();
    // purple::Paint paint;
    // paint.color = purple::ConverColorValue(purple::Color::Yellow);
    // shapeBatch->renderRect(rect , paint);
    // shapeBatch->end();

    // auto spriteBatch = purple::Engine::getRenderEngine()->getSpriteBatch();
    // spriteBatch->begin();
    // // purple::Rect colorRect = rect;
    // auto region = game->cubesTextureList[CubeColor::Gray];
    // spriteBatch->renderRegionImage(*region, rect);
    // spriteBatch->end();

    auto region = game->cubesTextureList[CubeColor::Gray];
    float left = rect.left;
    float top = rect.top;

    purple::Rect cubeRect(left , top , cubeSize , cubeSize);

    auto spriteBatch = purple::Engine::getRenderEngine()->getSpriteBatch();
    spriteBatch->begin();

    for(int i = 0; i < TetrisGame::ROW_COUNT ;i++){
        for(int j = 0; j < TetrisGame::COL_COUNT; j++){
            cubeRect.left = left + j * cubeSize;
            cubeRect.top = top - i * cubeSize;
            cubeRect.width = cubeSize;
            cubeRect.height = cubeSize;

            int dataType = this->game->gridData[i][j];
            if(dataType == GRID_TYPE_WALL){
                spriteBatch->renderRegionImage(*region, cubeRect);
            }
            
        }//end for j
    }//end for i

    spriteBatch->end();
}

