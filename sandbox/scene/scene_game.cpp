#include "scene/scene_game.h"
#include "purple_ui.h"
#include "panel/panel_main.h"
#include "panel/panel_score.h"
#include "panel/panel_next.h"
#include "tetris.h"

void SceneGame::init(){
    const float panelMainHeight = purple::Engine::ScreenHeight - PADDING * 2;
    cubeSize = panelMainHeight / TetrisGame::ROW_COUNT;
    const float panelMainWidth = cubeSize * TetrisGame::COL_COUNT;

    const float panelMainLeft = purple::Engine::ScreenWidth / 2.0f - panelMainWidth / 2.0f;
    const float panelMainTop = purple::Engine::ScreenHeight - PADDING;

    purple::Log::i("SceneGame", "panelMainSize: %f x %f" , panelMainWidth , panelMainHeight);

    panelMain = std::make_shared<PanelMain>(this->game , 
        cubeSize, panelMainLeft , panelMainTop , panelMainWidth , panelMainHeight);

    const float rightBoxLeft = panelMainLeft + panelMainWidth + PADDING;
    const float rightBoxWidth = purple::Engine::ScreenWidth - rightBoxLeft - PADDING;
    const float rightBoxTop = panelMainTop;

    panelScore = std::make_shared<PanelScore>(this->game, 
        2.0f * cubeSize ,
        rightBoxLeft , 
        rightBoxTop, 
        rightBoxWidth);

    panelNext = std::make_shared<PanelNext>(this->game);
}

void SceneGame::update(){
    if(game->state == Pause){
        //pause game do nothing
    }else if(game->state == Start){
        panelMain->update();
        panelScore->update();
        panelNext->update();
    }
}

void SceneGame::render(){
    panelMain->render();
    panelScore->render();
    panelNext->render();

    renderGamePauseUi();
}

void SceneGame::onInputEvent(purple::InputEvent &event){
    if(event.code == purple::CODE_KEY_ESCAPE 
        && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
        onEscKeyPressed();
    }
    
    if(game->state == Pause){
        if(event.code == purple::CODE_KEY_DOWN 
            && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
            onDownKeyPressed();
        }else if(event.code == purple::CODE_KEY_UP
            && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
            onUpKeyPressed();
        }else if(event.code == purple::CODE_KEY_ENTER
            && event.action == purple::EVENT_ACTION_KEYBOARD_PRESS){
            onEnterKeyPressed();
        }
    }else if(game->state == Start){
        if(panelMain != nullptr){
            panelMain->onInputEvent(event);
        }
    }
}

void SceneGame::pauseGame(){
    purple::Log::i("Tetris" , "pauseGame");

    if(this->game->state == Pause){
        return;
    }

    this->menuIndex = 0;
    game->preState = game->state;
    game->updateState(Pause);
    
    game->stopSound(game->audioBgm);
}

void SceneGame::resumeGame(){
    purple::Log::i("Tetris" , "resumeGame");

    if(game->state == Pause){
        game->updateState(game->preState);
    }
    game->playSound(game->audioBgm);
}

void SceneGame::renderGamePauseUi(){
    if(game->state != Pause){
        return;
    }

    purple::Rect screenRect(0, purple::Engine::ScreenHeight, 
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight);
    purple::Paint paint;
    paint.color = glm::vec4(0.0f, 0.0f , 0.0f , 0.9f);

    auto batch = purple::Engine::getRenderEngine()->getShapeBatch();
    batch->begin();
    batch->renderRect(screenRect , paint);
    batch->end();

    renderMenus();
}

void SceneGame::renderMenus(){
    using namespace purple;

    TextPaint textPaint;
    textPaint.textColor = ConverColorValue(Color::White);
    const float textHeight = 40.0f;
    const float padding = 16.0f;
    textPaint.setTextSize(textHeight);

    float totalHeight = (textHeight + padding) * menus.size();
    float top = purple::Engine::ScreenHeight / 2.0f  + totalHeight / 2.0f;

    for(int i = 0, len = menus.size() ; i < len ;i++){
        auto menuStr = menus[i];
        Rect textOutRect;
        Engine::getRenderEngine()->preCalculateTextSize(menuStr, textPaint, 
            purple::Engine::ScreenWidth, textOutRect);
        
        float textWidth = textOutRect.width;
        float menuLeftPos = purple::Engine::ScreenWidth / 2.0f - textWidth / 2.0f;

        textPaint.textColor = ColorTextUnselected;
        if(menuIndex == i){
            textPaint.textColor = ColorTextSelected;
        }
        
        Engine::getRenderEngine()->renderText(menuStr , menuLeftPos, 
            top , textPaint);
        top -= (textOutRect.height + padding);
    }//end for i
}

void SceneGame::onEscKeyPressed(){
    purple::Log::i("Tetris" , "onEsckeyPressed");

    if(this->game->state == Pause){
        resumeGame();
    }else{
        pauseGame();
    }
}

void SceneGame::onUpKeyPressed(){
    game->playSound(game->audioItemChange);
    if(menuIndex - 1 < 0){
        menuIndex = menus.size() - 1;
    }else{
        menuIndex = menuIndex - 1;
    }
}

void SceneGame::onDownKeyPressed(){
    game->playSound(game->audioItemChange);
    menuIndex = (menuIndex + 1)% menus.size();
}

void SceneGame::onEnterKeyPressed(){
    switch (menuIndex){
        case MENU_RESUME:
            resumeGame();
            break;
        case MENU_EXIT_SPLASH:
            if(game->gameScene != nullptr 
                && game->gameScene->panelMain != nullptr){
                game->gameScene->panelMain->onGameOver(true);
            }
            break;
        case MENU_EXIT_GAME:
            game->exitGame();
            break;
        default:
        break;
    }
}

void SceneGame::dispose(){

}

