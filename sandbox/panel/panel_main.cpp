
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
    if(state == UNSET){
        state = GenCube;
    }else if(state == GenCube){
        genNewCube();
        blitCubeToGridData();
        state = CubeDown;
    }else if(state == CubeDown){
        blitCubeToGridData();
    }else if(state == CubeDismiss){

    }
}

void PanelMain::genNewCube(){
    auto type = this->game->getNextTetrisType();
    this->currentShape = createShapeByType(type);
    this->currentShape->reset();
}

void PanelMain::currentTetrisDown(){

}

void PanelMain::blitCubeToGridData(){
    clearCubeGridData();

    if(currentShape == nullptr){
        return;
    }

    auto points = currentShape->getPoints();
    putGridData(points, currentShape->getColor());
    holderPoints = points;
}

void PanelMain::clearCubeGridData(){
    putGridData(holderPoints , GRID_TYPE_IDLE);
}

 void PanelMain::putGridData(std::vector<int> &points , int value){
    std::vector<std::vector<int>> &grid = game->gridData;
    const int len = points.size() / 2;
    for(int i = 0 ; i < len; i++){
        const int row = points[2 * i + 0];
        const int col = points[2 * i + 1];
        if(row >= 0 && row < TetrisGame::ROW_COUNT 
            && col >= 0 && col < TetrisGame::COL_COUNT){
            grid[row][col] = value;
        }
    } //end for i
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

void PanelMain::onInputEvent(purple::InputEvent &event){
    if(currentShape == nullptr){
        return;
    }

    if(event.code == purple::CODE_KEY_LEFT
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ //move left
        currentShape->moveLeft();
    }else if(event.code == purple::CODE_KEY_RIGHT 
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ // move right
        currentShape->moveRight();
    }else if(event.code == purple::CODE_KEY_DOWN
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ // move down
        currentShape->moveDown();
    }
}

