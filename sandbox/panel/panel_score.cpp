
#include "panel_score.h"
#include "tetris.h"
#include "purple_ui.h"

PanelScore::PanelScore(TetrisGame *game, float fontSize, float left
    ,float top, float width){
    this->game = game;
    this->fontSize = fontSize;

    this->top = top; 
    this->left = left;
    this->width = width;
    
}

void PanelScore::update(){
    // score++;
}

void PanelScore::render(){
    purple::TextPaint textPaint;
    textPaint.setTextSize(fontSize);
    textPaint.textColor = purple::ConverColorValue(purple::Color::White);
    textPaint.fontName = "youyuan";
    textPaint.textGravity = purple::TextGravity::Center; 

    purple::Rect titleRect(left , top , width, fontSize);
    purple::Engine::getRenderEngine()
        ->renderTextWithRect(L"得分" , titleRect, textPaint , nullptr);

    purple::Rect scoreRect(left , titleRect.getBottom() , width, fontSize);
    std::wstring scoreStr = std::to_wstring(this->score);
    purple::Engine::getRenderEngine()
        ->renderTextWithRect(scoreStr, scoreRect, textPaint , nullptr);
}