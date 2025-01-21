#include "panel_next.h"
#include "tetris.h"
#include "panel/panel_score.h"
#include "purple_ui.h"

PanelNext::PanelNext(TetrisGame *game_){
    this->game = game_;
}

void PanelNext::update(){
    purple::Rect headBox = this->game->gameScene->getPanelScore()->getContentRect();

    this->left = headBox.left;
    this->top = headBox.getBottom() - 20;
    this->width = headBox.width;
    this->height = 120.0f;
}

void PanelNext::render(){
    using namespace purple;

    purple::Rect wrapRect(left , top , width , height);
    purple::TextPaint textPaint;
    textPaint.textColor = purple::ConverColorValue(purple::Color::White);
    textPaint.textGravity = TextGravity::Center; 
    purple::Engine::getRenderEngine()->renderTextWithRect(L"下一个" , wrapRect, textPaint , nullptr);

    // auto batch = purple::Engine::getRenderEngine()->getShapeBatch();
    // batch->begin();

    // purple::Paint wrapRectPaint;
    // wrapRectPaint.color = purple::ConverColorValue(purple::Color::White);
    // batch->renderRect(wrapRect, wrapRectPaint);
    // batch->end();
}