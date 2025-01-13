
#include "panel_main.h"
#include "purple_ui.h"
#include "common.h"
#include "shape/shape.h"
#include "shape/ishape.h"

PanelMain::PanelMain(TetrisGame *game,
    float cubeSize,
    float left , float top , 
    float width , float height){
    
    this->game = game;
    this->cubeSize = cubeSize;

    rect.left = left;
    rect.top = top;
    rect.width = width;
    rect.height = height;

    auto type = this->game->getNextTetrisType();
    this->currentShape = createShapeByType(type);
}

std::shared_ptr<Shape> PanelMain::createShapeByType(int shapeType){
    std::shared_ptr<Shape> shape = nullptr;
    switch (shapeType){
    case TETRIS_TYPE_I:
        shape = std::make_shared<IShape>();
        break;
    case TETRIS_TYPE_J:
        shape = std::make_shared<IShape>();
        break;
    case TETRIS_TYPE_L:
        shape = std::make_shared<IShape>();
        break;
    case TETRIS_TYPE_O:
        shape = std::make_shared<IShape>();
        break;
    case TETRIS_TYPE_S:
        shape = std::make_shared<IShape>();
        break;
    case TETRIS_TYPE_T:
        shape = std::make_shared<IShape>();
        break;
    case TETRIS_TYPE_Z:
        shape = std::make_shared<IShape>();
        break;
    default:
        break;
    }//end switch
    return shape;
}

void PanelMain::update(){
    if(currentShape == nullptr){
        return;
    }

    auto points = currentShape->getPoints();
    
    // for(int i = 0 ;i < 8 ;i++){
    //     std::cout << points[i] << "\t";
    // } 
    // std::cout << std::endl;

    game->gridData[points[0]][points[1]] = currentShape->getColor();
    game->gridData[points[2]][points[3]] = currentShape->getColor();
    game->gridData[points[4]][points[5]] = currentShape->getColor();
    game->gridData[points[6]][points[7]] = currentShape->getColor();
}

void PanelMain::currentTetrisDown(){

}

void PanelMain::render(){
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
                auto region = game->cubesTextureList[CubeColor::Gray];
                spriteBatch->renderRegionImage(*region, cubeRect);
            }else if(dataType == GRID_TYPE_IDLE){
                //render nothing
            }else if(dataType > 0){
                auto region = game->cubesTextureList[dataType];
                spriteBatch->renderRegionImage(*region, cubeRect);
            }
        }//end for j
    }//end for i

    spriteBatch->end();
}

