
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
        std::cout << "can not move to right!!" << std::endl;
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
