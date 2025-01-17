
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
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_J:
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_L:
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_O:
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_S:
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_T:
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_Z:
        shape = std::make_shared<IShape>(game);
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
        state = CubeDown;
        timeRecord = 0;
    }else if(state == CubeDown){
        long deltaTime = this->game->deltaTimeMils;
        timeRecord += deltaTime;

        if(timeRecord >= this->game->updateDelayMils){
            // purple::Log::e("Tetris" , "Tetris update once! %ld" , timeRecord);
            timeRecord = 0;
            currentTetrisDown();
        }
    }else if(state == Blit){
        checkDismissGrid();
        if(willDismissRows.empty()){//没有需要消失的行
            state = GenCube;
        }else{ // 找到需要消失的行
            state = CubeDismiss;
        }
    }else if(state == CubeDismiss){
        dismissGridRows();
        state = GenCube;
    }else if(state == GameOver){
        game->state = GameState::Splash;
    }
}

void PanelMain::genNewCube(){
    auto type = this->game->getNextTetrisType();
    this->currentShape = createShapeByType(type);
    this->currentShape->reset();

    checkIsGameOver();
}

void PanelMain::checkIsGameOver(){
    if(this->currentShape == nullptr){
        return;
    }

    for(int i = 1; i < TetrisGame::COL_COUNT - 1 ;i++){
        if(game->gridData[0][i] > 0){
            onGameOver();
        }
    }
}

void PanelMain::onGameOver(){
    this->game->state = Splash;

    for(int i = 0; i < TetrisGame::ROW_COUNT - 1 ;i++){
        for(int j = 1 ; j < TetrisGame::COL_COUNT - 1 ; j++){
            this->game->gridData[i][j] = GRID_TYPE_IDLE;
        }
    }
}

void PanelMain::currentTetrisDown(){
    purple::Log::w("Tetris" , "currentTetris Down");
    
    if(currentShape != nullptr){
        currentShape->moveDown();
    }
}

void PanelMain::blitTetrisToGrid(){
    this->state = Blit;
    if(currentShape == nullptr){
        return;
    }

    std::vector<int> &points = currentShape->getPoints();
    const int len = points.size() >> 1;
    for(int i = 0; i < len ; i++){
        const int row = points[(i << 1)];
        const int col = points[(i << 1) + 1];

        if(Shape::checkRowColInRange(row , col)){
            game->gridData[row][col] = currentShape->getColor();
            // game->gridData[row][col] = CubeColor::Gray;
        }
    }//end for i

    currentShape = nullptr;
}

void PanelMain::checkDismissGrid(){
    willDismissRows.clear();
    
    for(int i = TetrisGame::ROW_COUNT - 2; i >=0 ;i--){
        bool canDismiss = true;
        for(int j = 1 ; j < TetrisGame::COL_COUNT - 1 ;j++){
            if(game->gridData[i][j] <= 0){
                canDismiss = false;
                break;
            }
        }//end for j

        if(canDismiss){
            willDismissRows.push_back(i);
        }
    }//end for i
}

void PanelMain::dismissGridRows(){
    if(willDismissRows.empty()){
        return;
    }

    auto copyGrids = game->gridData;
    //clear
    for(int i = 0 ; i < TetrisGame::ROW_COUNT -1 ;i++){
        for(int j = 1; j< TetrisGame::COL_COUNT - 1 ; j++){
            copyGrids[i][j] = GRID_TYPE_IDLE;
        }//end for j
    }//end for i

    std::map<int, int> dismissRowMap;
    for(auto &value : willDismissRows){
        dismissRowMap[value] = value;
    }//end for each

    //copy
    int originRowIndex = TetrisGame::ROW_COUNT -1;
    for(int i = TetrisGame::ROW_COUNT -1 ; i >= 0;i--){
        if(dismissRowMap.find(i) == dismissRowMap.end()){//不是需要消失的行
            for(int j = 1; j< TetrisGame::COL_COUNT - 1 ; j++){
                copyGrids[originRowIndex][j] = game->gridData[i][j];
            }//end for j
            originRowIndex--;
        }
    }//end for i

    game->gridData = copyGrids;
}

void PanelMain::render(){
    renderGrids();

    if(currentShape != nullptr){
        currentShape->render();
    }
}


void PanelMain::renderGrids(){
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
            }else if(dataType > 0){ // render color cube
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
    }else if(event.code == purple::CODE_KEY_UP
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ // move up
        currentShape->moveUp();
    }else if(event.code == purple::CODE_KEY_ENTER
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ // roate
        currentShape->rotate();
    }
}

