#include "scene/scene_splash.h"
#include "purple_ui.h"
#include "render/sprite.h"
#include "tetris.h"
#include "audio/audio.h"

void SceneSplash::init(){
    logoImage = purple::BuildImageByAsset("img/logo.png");

    logoTop = purple::Engine::ScreenHeight - 120;
    logoWidth = purple::Engine::ScreenHeight / 1.5f;

    audioItemChange = purple::AudioManager::getInstance()
        ->loadAudioEntity("audio/menu_item_change.mp3");
}

void SceneSplash::dispose(){
    if(audioItemChange != nullptr){
        purple::AudioManager::getInstance()->releaseAudioEntity(audioItemChange);
    }
}

void SceneSplash::onInputEvent(purple::InputEvent &event){
    // purple::Log::i("SceneSplash" , "input event %d , %d", event.action , event.code);
    if(event.code == purple::CODE_KEY_UP && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
        selectPriorMenuItem();
    }else if(event.code == purple::CODE_KEY_DOWN && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
        selectNextMenuItem();
    }else if(event.code == purple::CODE_KEY_ENTER && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
        pressEnterKey();
    }
}

void SceneSplash::pressEnterKey(){
    purple::Log::i("SceneSplash" , "pressEnterKey");

    purple::AudioManager::getInstance()->playAudioEntity(audioItemChange);

    if(currentMenuIndex == MENU_START_GAME){
        game->updateState(GameState::Start);
    }else if(currentMenuIndex == MENU_EXIT_GAME){
        game->exitGame();
    }
}

void SceneSplash::selectNextMenuItem(){
    purple::Log::i("SceneSplash" , "selectNextMenuItem");
    purple::AudioManager::getInstance()->playAudioEntity(audioItemChange);

    currentMenuIndex = (currentMenuIndex + 1) % menuNames.size();
    purple::Log::i("SceneSplash" , "currentMenuIndex = %d" , currentMenuIndex);
}

void SceneSplash::selectPriorMenuItem(){
    purple::Log::i("SceneSplash" , "selectPriorMenuItem");
    purple::AudioManager::getInstance()->playAudioEntity(audioItemChange);

    const int newIndex = currentMenuIndex - 1;
    if(newIndex < 0){
        currentMenuIndex = menuNames.size() - 1;
    }else{
        currentMenuIndex = newIndex;
    }
    purple::Log::i("SceneSplash" , "currentMenuIndex = %d" , currentMenuIndex);
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

