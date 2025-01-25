#include "gamepad.h"
#include "purple.h"
#include "utils.h"
#include "input/input_manager.h"
#include "input/input_common.h"

GamePadInput::GamePadInput(){
    initButtons();
}

void GamePadInput::initButtons(){
    for(auto &type : listenButtonTypes){
        buttonStates[type] = {type, 0 , false};
    }//end for each
}


void GamePadInput::updateButtonState(){
    int result = glfwJoystickPresent(GLFW_JOYSTICK_1);
    // std::cout << "result =  " << result<< std::endl;
    if(result == GLFW_FALSE){//not found joystick
        return;
    }

    result = glfwJoystickIsGamepad(GLFW_JOYSTICK_1);
    if(result == GLFW_FALSE){//not found gamepad
        return;
    }

    GLFWgamepadstate state;
    if(glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
        for(auto &glfwButtonType : listenButtonTypes){
            GamePadButtonState& oldBtnState = buttonStates[glfwButtonType];
            const long curTime = purple::currentTimeMillis();
            if(state.buttons[glfwButtonType]){ //button is pressed
                if(!oldBtnState.isPressed){
                    oldBtnState.time = curTime;
                    // std::cout << "type:" << type << " pressed" << std::endl;
                    postPressdEvent(glfwButtonType);
                }else{
                    //repeat
                    if(curTime - oldBtnState.time >= REPEAT_DUR_MILLS){
                        oldBtnState.time = curTime;
                        postRepeatEvent(glfwButtonType);
                    }
                }
                oldBtnState.isPressed = true;
            }else{//release
                if(oldBtnState.isPressed){
                    // std::cout << "type:" << type << " released" << std::endl;
                    postReleaseEvent(glfwButtonType);
                }
                oldBtnState.isPressed = false;
                oldBtnState.time = curTime;
            }
        }//end for each
    }
}

void GamePadInput::postPressdEvent(int glfwButtonCode){
    purple::InputEvent event;
    event.action = purple::EVENT_ACTION_KEYBOARD_PRESS;
    event.code = convertGlfwCode(glfwButtonCode);
    purple::InputManager::getInstance()->onEvent(event);

}

void GamePadInput::postReleaseEvent(int glfwButtonCode){
    purple::InputEvent event;
    event.action = purple::EVENT_ACTION_KEYBOARD_RELEASE;
    event.code = convertGlfwCode(glfwButtonCode);
    purple::InputManager::getInstance()->onEvent(event);
}
void GamePadInput::postRepeatEvent(int glfwButtonCode){
    purple::InputEvent event;
    event.action = purple::EVENT_ACTION_KEYBOARD_REPEAT;
    event.code = convertGlfwCode(glfwButtonCode);
    purple::InputManager::getInstance()->onEvent(event);
}

int GamePadInput::convertGlfwCode(int glfwButtonCode){
    int code = -1;
    switch(glfwButtonCode){
        case GLFW_GAMEPAD_BUTTON_DPAD_UP:
            code = purple::CODE_KEY_UP;
            break;
         case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:
            code = purple::CODE_KEY_DOWN;
            break;
         case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:
            code = purple::CODE_KEY_LEFT;
            break;
        case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:
            code = purple::CODE_KEY_RIGHT;
            break;
        case GLFW_GAMEPAD_BUTTON_A:
            code = purple::CODE_KEY_ENTER;
            break;
        case GLFW_GAMEPAD_BUTTON_START:
            code = purple::CODE_KEY_ESCAPE;
            break;
        default:
            break;
    }
    return code;
}

GamePadInput::~GamePadInput(){

}

