
#include "shape/shape.h"
#include <iostream>
#include "purple.h"
#include "tetris.h"
#include "scene/scene_game.h"
#include "panel/panel_main.h"
#include <memory>
#include "purple_ui.h"

Shape::Shape(TetrisGame *game){
    this->game = game;
}

CubeColor Shape::getColor(){
    return CubeColor::Gray;
}

glm::vec4 Shape::getShaodowColor(){
    CubeColor cubeColor = getColor();
    glm::vec4 shadowColor = purple::ConverColorValue(purple::Color::White);
    switch (cubeColor){
    case Yellow:
        shadowColor = purple::ConverColorValue(purple::Color::Yellow);
        break;
    case Cyan:
        shadowColor = purple::ConverColorValue(purple::Color::Cyan);
        break;
    case Red:
        shadowColor = purple::ConverColorValue(purple::Color::Red);
        break;
    case Blue:
        shadowColor = purple::ConverColorValue(purple::Color::SkyBlue);
        break;
    case Green:
        shadowColor = purple::ConverColorValue(purple::Color::Green);
        break;
    case Orange:
        shadowColor = purple::ConverColorValue(purple::Color::Orange);
        break;
    case Purple:
        shadowColor = purple::ConverColorValue(purple::Color::Purple);
        break;
    case Gray:
        shadowColor = purple::ConverColorValue(purple::Color::Gray);
        break;
    default:
        break;
    }
    return shadowColor;
}

void Shape::reset(){
}

void Shape::moveLeft(){
    game->playSound(game->audioCubeRotate);
    onMoveLeft();
}

void Shape::moveRight(){
    game->playSound(game->audioCubeRotate);
    onMoveRight();
}

void Shape::moveDown(){
    // game->playSound(game->audioCubeRotate);
    onMoveDown();
}

void Shape::moveUp(){
    onMoveUp();
}

void Shape::rotate(){
    game->playSound(game->audioCubeRotate);
    onRotate();
}

void Shape::onMoveLeft(){
    if(!checkAllCubesCanMoveLeft()){
        return;
    }

    const int len = points.size() >> 1;
    for(int i = 0 ; i < len ; i++){
        int col = points[(i << 1) + 1];
        points[(i << 1) + 1] = col - 1;
    }//end for i
}

void Shape::onMoveRight(){
    if(!checkAllCubesCanMoveRight()){
        // std::cout << "can not move to right!!" << std::endl;
        return;
    }

    const int len = points.size() >> 1;
    for(int i = 0 ; i < len ; i++){
        int col = points[ (i << 1) + 1];
        points[(i << 1) + 1] = col + 1;
    }//end for i
}

void Shape::onMoveDown(){
    if(!checkAllCubesCanMoveDown()){
        return;
    }

    const int len = points.size() >> 1;
    for(int i = 0 ; i < len ; i++){
        int row = points[(i << 1)];
        points[(i << 1)] = row + 1;
    }//end for i
}

void Shape::onMoveUp(){
}

void Shape::onRotate(){
}

int Shape::getShapeWidth(){
    return 0;
}

bool Shape::checkAllCubesCanMoveLeft(){
    const int len = points.size() >> 1;
    for(int i = 0 ; i < len; i++){
        const int row = points[(i << 1)];
        const int col = points[(i << 1) + 1];
        if(checkRowColInRange(row, col - 1)){
            if(this->game->gridData[row][col - 1] > 0){
                return false;
            }
        }else if(col <= 1){
            return false;
        }
    }//end for i
    return true;
}

bool Shape::checkAllCubesCanMoveRight(){
    const int len = points.size() >> 1;
    for(int i = 0 ; i < len; i++){
        const int row = points[(i << 1)];
        const int col = points[(i << 1) + 1];
        
        if(checkRowColInRange(row, col + 1)){
            // std::cout << "row : " << row << " col :" << (col+1) << std::endl;
            if(this->game->gridData[row][col + 1] > 0){
                return false;
            }
        }else if((col + 1) >= (TetrisGame::COL_COUNT - 1)){
            // std::cout << "xxx row : " << row << " col :" << (col+1) << std::endl;
            return false;
        }
    }//end for i
    return true;
}

bool Shape::checkAllCubesCanMoveDown(){
    const int len = points.size() >> 1;
    for(int i = 0 ; i < len; i++){
        const int row = points[(i << 1)];
        const int col = points[(i << 1) + 1];
        if(checkRowColInRange(row + 1, col)){
            if(this->game->gridData[row + 1][col] > 0){
                return false;
            }
        }
    }//end for i
    return true;
}

bool Shape::checkRowColInRange(int row , int col){
    return row >= 0 && row < TetrisGame::ROW_COUNT 
        && col >=0 && col < TetrisGame::COL_COUNT;
}

void Shape::update(float left , float top , float cubeSize){
    this->left = left;
    this->top = top;
    this->cubeSize = cubeSize;
}

void Shape::render(){
    // const float cubeSize = this->game->gameScene->cubeSize;
    // auto gamePanelRect = this->game->gameScene->panelMain->rect;

    purple::Rect cubeRect;
    cubeRect.width = cubeSize;
    cubeRect.height = cubeSize;

    auto spriteBatch = purple::Engine::getRenderEngine()->getSpriteBatch();
    spriteBatch->begin();
    const int len = this->points.size() / 2;
    for(int i = 0 ; i < len ;i++){
        const int row = points[(i << 1)];
        const int col = points[(i << 1) + 1];

        cubeRect.left = this->left + col * cubeSize;
        cubeRect.top = this->top - row * cubeSize;
        
        auto region = game->getCubeImageRegionByColor(getColor());
        spriteBatch->renderRegionImage(*region, cubeRect);
    }//end for i
    spriteBatch->end();
}

void Shape::renderShadow(){
    using namespace purple;
    purple::Paint paint;
    paint.fillStyle = FillStyle::Stroken;
    paint.stokenWidth = 1.0f;
    paint.color = getShaodowColor();
    // paint.color[3] = 0.6f;
    
    std::vector<int> originPoints = points;
    const int len = originPoints.size() >> 1;

    purple::Rect cubeRect;
    cubeRect.width = cubeSize;
    cubeRect.height = cubeSize;

    auto shapeBatch = purple::Engine::getRenderEngine()->getShapeBatch();
    shapeBatch->begin();
    for(int i = 0 ;i < len ;i++){
        int row = originPoints[i << 1];
        row += findShadowShapeRowOffset();
        const int col = originPoints[(i << 1) + 1];

        cubeRect.left = this->left + col * cubeSize;
        cubeRect.top = this->top - row * cubeSize;
        shapeBatch->renderRect(cubeRect , paint);
    }//end for i
    shapeBatch->end();
}

/**
 * @brief 
 *       1
 *     1 1
 *       1
 * 
 * 1 1 1 0 1
 * 1 1 1 1 1
 * @return int 
 */
int Shape::findShadowShapeRowOffset(){
    if(game == nullptr){
        return 0;
    }

    std::vector<int> originPoints = points;
    const int len = originPoints.size() >> 1;
    int offset = TetrisGame::ROW_COUNT;
    for(int i = 0 ;i < len ;i++){
        const int row = originPoints[i << 1];
        const int col = originPoints[(i << 1) + 1];

        int rowIndex = row;
        while(rowIndex <= TetrisGame::ROW_COUNT){
            if(rowIndex >=0 && 
                game->gridData[rowIndex][col] != GRID_TYPE_IDLE){
                break;
            }
            rowIndex++;
        }//end for while

        const int rowDeltaValue = rowIndex - row - 1;
        if(rowDeltaValue < offset){
            offset = rowDeltaValue;
        }
    }//end for i
    // std::cout << "offset = " << offset << std::endl;
    return offset;
}

std::vector<int>& Shape::getPoints(){
    return points;
}

bool Shape::checkPointsOverlayGrid(std::vector<int> &inputPoints){
    if(game == nullptr){
        return false;
    }

    const int len = inputPoints.size() >> 1;
    for(int i = 0 ; i < len; i++){
        const int row = inputPoints[(i << 1)];
        const int col = inputPoints[(i << 1) + 1];
        
        if(Shape::checkRowColInRange(row, col)
            && game->gridData[row][col] > 0){
            return true;
        }
    }//end for i
    return false;
}

Shape::~Shape(){
}
