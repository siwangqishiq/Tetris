
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

Shape::~Shape(){
}
