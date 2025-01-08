#include "scene_game.h"
#include "purple_ui.h"


void SceneGame::init(){

}

void SceneGame::update(){

}

void SceneGame::render(){
    using namespace purple;

    auto textRender = Engine::getRenderEngine()->getTextRender();
    Rect rect(0.0f, purple::Engine::ScreenHeight
        , purple::Engine::ScreenWidth,  purple::Engine::ScreenHeight);
    TextPaint textPaint;
    textPaint.setTextSize(130.0f);
    textPaint.textColor = ConverColorValue(Color::Red);
    textPaint.textGravity = TextGravity::Center;
    Engine::getRenderEngine()->renderTextWithRect(L"GAME START", rect , textPaint , nullptr);
}

