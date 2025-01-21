#include "panel_next.h"
#include "tetris.h"
#include "panel/panel_score.h"
#include "purple_ui.h"
#include "render/text_render.h"
#include "panel/panel_main.h"
#include "shape/shape.h"

PanelNext::PanelNext(TetrisGame *game_){
    this->game = game_;
}

void PanelNext::nextTetrisChanged(int newNext){
    this->nextTetrisType = newNext;
    nextShape = PanelMain::createShapeByType(nextTetrisType , game);
    if(nextShape != nullptr){
        nextShape->reset();
        adjustShapePoints();
    }
}

void PanelNext::adjustShapePoints(){
    //adjust
    std::vector<int> points = nextShape->getPoints();
    int minCol = points[1];
    int len = points.size() >> 1;
    for(int i = 1; i < len ;i++){
        if(minCol > points[(i << 1) + 1]){
            minCol = points[(i << 1) + 1];
        }
    }

    const int deltaCol = minCol;
    std::vector<int> newPoints = points;
    len = newPoints.size() >> 1;
    for(int i = 0 ; i < len ;i++){
        newPoints[(i << 1)] = points[(i << 1)];
        newPoints[(i << 1) + 1] = points[(i << 1) + 1] - deltaCol;
    }//end for i
    nextShape->setPoints(newPoints);
}

void PanelNext::update(){
    purple::Rect headBox = this->game->gameScene->getPanelScore()->getContentRect();

    this->left = headBox.left;
    this->top = headBox.getBottom() - 20;
    this->width = headBox.width;
    this->height = 100.0f;
}

void PanelNext::render(){
    using namespace purple;

    purple::Rect wrapRect(left , top , width , height);
    purple::TextPaint textPaint;
    textPaint.textColor = purple::ConverColorValue(purple::Color::White);
    textPaint.textGravity = TextGravity::Center; 

    purple::TextRenderOutInfo textOutInfo;
    purple::Engine::getRenderEngine()->renderTextWithRect(L"下一个" , 
        wrapRect, textPaint, &textOutInfo);

    if(nextTetrisType < 0 || nextShape == nullptr){
        return;
    }

    const int textHeight = textOutInfo.outRect.height;
    const float colOffset = nextShape->getShapeWidth() / 2.0f;
    nextShape->update(left + width / 2.0f - colOffset, 
        top - height - textHeight, this->game->gameScene->cubeSize);
    nextShape->render();
}