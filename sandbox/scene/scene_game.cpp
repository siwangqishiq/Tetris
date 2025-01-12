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

    panelScore = std::make_shared<PanelScore>(this->game, 2.0f * cubeSize ,
        rightBoxLeft , rightBoxTop, rightBoxWidth);
}

void SceneGame::update(){
    panelMain->update();
    panelScore->update();
}

void SceneGame::render(){
    // using namespace purple;
    // auto textRender = Engine::getRenderEngine()->getTextRender();
    // Rect rect(0.0f, purple::Engine::ScreenHeight
    //     , purple::Engine::ScreenWidth,  purple::Engine::ScreenHeight);
    // TextPaint textPaint;
    // textPaint.setTextSize(130.0f);
    // textPaint.textColor = ConverColorValue(Color::Red);
    // textPaint.textGravity = TextGravity::Center;
    // Engine::getRenderEngine()->renderTextWithRect(L"GAME START", rect , textPaint , nullptr);
    
    panelMain->render();
    panelScore->render();
}

void SceneGame::dispose(){

}

