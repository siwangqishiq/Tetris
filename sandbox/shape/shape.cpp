
#include "shape/shape.h"
#include <iostream>
#include "purple.h"
#include "tetris.h"
#include "scene/scene_game.h"
#include "panel/panel_main.h"
#include <memory>

Shape::Shape(TetrisGame *game){
    this->game = game;
}

CubeColor Shape::getColor(){
    return CubeColor::Gray;
}

void Shape::reset(){
}

void Shape::moveLeft(){
    onMoveLeft();
}

void Shape::moveRight(){
    onMoveRight();
}

void Shape::moveDown(){
    onMoveDown();

    if(!checkAllCubesCanMoveDown()){ //不可下降
        game->gameScene->panelMain->blitTetrisToGrid();
    }
}

void Shape::moveUp(){
    onMoveUp();
}

void Shape::rotate(){
    onRotate();
}

void Shape::onMoveLeft(){
}

void Shape::onMoveRight(){
}

void Shape::onMoveDown(){
}

void Shape::onMoveUp(){
}

void Shape::onRotate(){
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
            // std::cout << "row : " << row << " col :" << (col+1) 
            //     << "  data= " << this->game->gridData[row][col + 1]
            //     << std::endl;
            if(this->game->gridData[row][col + 1] > 0){
                return false;
            }
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

void Shape::render(){
    const float cubeSize = this->game->gameScene->cubeSize;
    auto gamePanelRect = this->game->gameScene->panelMain->rect;

    purple::Rect cubeRect;
    cubeRect.width = cubeSize;
    cubeRect.height = cubeSize;

    auto spriteBatch = purple::Engine::getRenderEngine()->getSpriteBatch();
    spriteBatch->begin();
    const int len = this->points.size() / 2;
    for(int i = 0 ; i < len ;i++){
        const int row = points[2*i + 0];
        const int col = points[2*i + 1];

        cubeRect.left = gamePanelRect.left + col * cubeSize;
        cubeRect.top = gamePanelRect.top - row * cubeSize;

        auto region = game->cubesTextureList[getColor()];
        spriteBatch->renderRegionImage(*region, cubeRect);
    }//end for i
    spriteBatch->end();
}

std::vector<int>& Shape::getPoints(){
    return points;
}

bool Shape::checkPointsOverlayGrid(std::vector<int> &inputPoints){
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
