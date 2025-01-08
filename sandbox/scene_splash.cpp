#include "scene_splash.h"
#include "purple_ui.h"
#include "render/sprite.h"

void SceneSplash::init(){
    logoImage = purple::BuildImageByAsset("img/logo.png");

    logoTop = purple::Engine::ScreenHeight - 120;
    logoWidth = purple::Engine::ScreenHeight / 1.5f;
}

void SceneSplash::update(){
    logoLeft = purple::Engine::ScreenWidth / 2.0f - logoWidth / 2.0f;
    
    float ratio = static_cast<float>(logoImage->getWidth()) / static_cast<float>(logoImage->getHeight());
    // std::cout << "ratio = " << ratio << std::endl;
    logoHeight = logoWidth / ratio;
    // std::cout << "logoW = " << logoWidth << "logoHeight = " << logoHeight << std::endl;
}

void SceneSplash::render(){
    using namespace purple;

    Rect logoSrcRect = logoImage->getRect();
    Rect logoDstRect(logoLeft , logoTop , logoWidth , logoHeight);    

    auto spriteBatch = Engine::getRenderEngine()->getSpriteBatch();
    spriteBatch->begin();
    spriteBatch->renderImage(logoImage, logoSrcRect , logoDstRect);
    spriteBatch->end();

    auto textRender = Engine::getRenderEngine()->getTextRender();
    
    TextPaint textPaint;
    textPaint.textColor = ConverColorValue(Color::White);
    const float textHeight = 40.0f;
    textPaint.setTextSize(textHeight);

    float menuBottomPos = logoDstRect.getBottom() - 30.0f - textHeight;

    for(int i = 0, len = menuNames.size() ; i < len ;i++){
        auto menuStr = menuNames[i];
        Rect textOutRect;
        Engine::getRenderEngine()->preCalculateTextSize(menuStr, textPaint, 
            purple::Engine::ScreenWidth, textOutRect);
        
        float textWidth = textOutRect.width;
        float menuLeftPos = purple::Engine::ScreenWidth / 2.0f - textWidth / 2.0f;
        
        if(i == currentMenuIndex){
            textPaint.textColor = ColorTextSelected;
        }else{
            textPaint.textColor = ColorTextUnselected;
        }
        
        Engine::getRenderEngine()->renderText(menuStr , menuLeftPos, 
            menuBottomPos , textPaint);
        menuBottomPos -= (20.0f + textHeight);
    }//end for i
}

