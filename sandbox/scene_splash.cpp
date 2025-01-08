#include "scene_splash.h"
#include "purple_ui.h"

void SceneSplash::init(){
    
}

void SceneSplash::update(){
    
}

void SceneSplash::render(){
    using namespace purple;

    auto textRender = Engine::getRenderEngine()->getTextRender();
    Rect rect(0.0f, purple::Engine::ScreenHeight
        , purple::Engine::ScreenWidth,  purple::Engine::ScreenHeight);
    TextPaint textPaint;
    textPaint.setTextSize(100.0f);
    textPaint.textColor = ConverColorValue(Color::Silver);
    textPaint.textGravity = TextGravity::Center;
    Engine::getRenderEngine()->renderTextWithRect(L"Terris\n俄罗斯方块", rect , textPaint , nullptr);
}

