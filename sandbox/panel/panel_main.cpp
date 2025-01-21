
#include "panel_main.h"
#include "purple_ui.h"
#include "common.h"
#include "shape/shape.h"
#include "shape/ishape.h"
#include "shape/lshape.h"
#include "shape/oshape.h"
#include "shape/sshape.h"
#include "shape/tshape.h"
#include "shape/zshape.h"
#include "shape/jshape.h"
#include "panel/panel_score.h"
#include "panel/panel_next.h"

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

std::shared_ptr<Shape> PanelMain::createShapeByType(int shapeType , TetrisGame *game){
    std::shared_ptr<Shape> shape = nullptr;
    switch (shapeType){
    case TETRIS_TYPE_I:
        shape = std::make_shared<IShape>(game);
        break;
    case TETRIS_TYPE_J:
        shape = std::make_shared<JShape>(game);
        break;
    case TETRIS_TYPE_L:
        shape = std::make_shared<LShape>(game);
        break;
    case TETRIS_TYPE_O:
        shape = std::make_shared<OShape>(game);
        break;
    case TETRIS_TYPE_S:
        shape = std::make_shared<SShape>(game);
        break;
    case TETRIS_TYPE_T:
        shape = std::make_shared<TShape>(game);
        break;
    case TETRIS_TYPE_Z:
        shape = std::make_shared<ZShape>(game);
        break;
    default:
        shape = nullptr;
        break;
    }//end switch
    return shape;
}

void PanelMain::update(){
    // if(currentShape != nullptr){
    // }

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
    game->genNextTertisType();

    game->playSound(game->audioCubeMove);

    onNextTetrisChanged();

    currentShape = createShapeByType(type , this->game);
    currentShape->reset();

    checkIsGameOver();
}

void PanelMain::onNextTetrisChanged(){
    purple::Log::i("Tetris" , "onNextTetrisChanged = %d" , this->game->getNextTetrisValue());
    auto panelNext = game->gameScene->panelNext;
    if(panelNext != nullptr){
        const int newTetrisType = this->game->getNextTetrisValue();
        panelNext->nextTetrisChanged(newTetrisType);
    }
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
    game->stopSound(game->audioBgm);
    game->playSound(game->audioFailed);

    this->game->state = Splash;

    for(int i = 0; i < TetrisGame::ROW_COUNT - 1 ;i++){
        for(int j = 1 ; j < TetrisGame::COL_COUNT - 1 ; j++){
            this->game->gridData[i][j] = GRID_TYPE_IDLE;
        }
    }//end for i

    auto panelScore = game->gameScene->getPanelScore();
    if(panelScore != nullptr){
        panelScore->resetScore();
    }
}

void PanelMain::currentTetrisDown(){
    purple::Log::w("Tetris" , "currentTetris Down");

    if(currentShape != nullptr){
        if(!currentShape->checkAllCubesCanMoveDown()){ //不可下降
            game->playSound(game->audioCubeMove);
            game->gameScene->panelMain->blitTetrisToGrid();
            return;
        }else{
            currentShape->moveDown();
        }
    }
}

void PanelMain::blitTetrisToGrid(){
    this->state = Blit;
    if(currentShape == nullptr){
        return;
    }

    std::vector<int> &points = currentShape->getPoints();

    // for(auto &v : points){
    //     std::cout << v << " ";
    // }
    // std::cout << "\n";

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

    // std::cout << "dismissGridRows size = " << willDismissRows.size() << std::endl;

    game->playSound(game->audioCubeDismiss);
    
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

    addScores();
    willDismissRows.clear();
}

void PanelMain::addScores(){
    const int dismissRowCount = willDismissRows.size();

    int addScore = 0;
    switch(dismissRowCount){
        case 1:
            addScore = 10;
            break;
        case 2:
            addScore = 22;
            break;
        case 3:
            addScore = 35;
            break;
        case 4:
            addScore = 50;
            break;
        default:
            break;
    }//end switch

    auto panelScore = game->gameScene->getPanelScore();
    if(panelScore != nullptr){
        panelScore->addScore(addScore);
    }
}

void PanelMain::render(){
    renderGrids();

    if(currentShape != nullptr){
        const float cubeSize = this->game->gameScene->cubeSize;
        auto gamePanelRect = this->game->gameScene->panelMain->rect;
        currentShape->update(gamePanelRect.left , gamePanelRect.top , cubeSize);
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
                auto region = game->getCubeImageRegionByColor(CubeColor::Gray);
                spriteBatch->renderRegionImage(*region, cubeRect);
            }else if(dataType == GRID_TYPE_IDLE){
                //render nothing
            }else if(dataType > 0){ // render color cube
                auto region = game->getCubeImageRegionByColor(dataType);
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
        && (event.action == purple::EVENT_ACTION_KEYBOARD_PRESS 
            || event.action == purple::EVENT_ACTION_KEYBOARD_REPEAT)){ //move left
        currentShape->moveLeft();
    }else if(event.code == purple::CODE_KEY_RIGHT 
        && (event.action == purple::EVENT_ACTION_KEYBOARD_PRESS
            || event.action == purple::EVENT_ACTION_KEYBOARD_REPEAT)){ // move right
        currentShape->moveRight();
    }else if(event.code == purple::CODE_KEY_DOWN
        && (event.action == purple::EVENT_ACTION_KEYBOARD_PRESS
            || event.action == purple::EVENT_ACTION_KEYBOARD_REPEAT)){ // move down
        onPressKeyDown();
    }else if(event.code == purple::CODE_KEY_UP
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ // move up
        currentShape->moveUp();
    }else if((event.code == purple::CODE_KEY_ENTER || event.code == purple::CODE_KEY_SPACE)
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){ // roate
        currentShape->rotate();
    }
}

void PanelMain::onPressKeyDown(){
    if(currentShape != nullptr){
        if(currentShape->checkAllCubesCanMoveDown()){
            game->playSound(game->audioCubeRotate);
            currentShape->moveDown();
            timeRecord = 0;

            if(!currentShape->checkAllCubesCanMoveDown()){
                game->gameScene->panelMain->blitTetrisToGrid();
            }
        }else{
            blitTetrisToGrid();
        }
    }
}

