#include "tetris.h"
#include "purple.h"
#include "purple_ui.h"

void TetrisGame::onInit(){
    
}

void TetrisGame::onTick(){
    using namespace purple;

    auto textRender = Engine::getRenderEngine()->getTextRender();
    Rect rect(0.0f, purple::Engine::ScreenHeight
        , purple::Engine::ScreenWidth,  purple::Engine::ScreenHeight);
    TextPaint textPaint;
    textPaint.textColor = ConverColorValue(Color::Silver);
    textPaint.textGravity = TextGravity::Center;
    Engine::getRenderEngine()->renderTextWithRect(L"Terris", rect , textPaint , nullptr);
}

void TetrisGame::onDispose(){

}


