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
    }
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
    purple::Engine::getRenderEngine()->renderTextWithRect(L"下一个" , wrapRect, textPaint , 
        &textOutInfo);

    if(nextTetrisType < 0 || nextShape == nullptr){
        return;
    }

    const int textHeight = textOutInfo.outRect.height;
    nextShape->update(left, top - height - textHeight, this->game->gameScene->cubeSize);
    nextShape->render();
}