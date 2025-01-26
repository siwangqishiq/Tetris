#pragma once

#include <unordered_map>
#include <vector>

#ifndef __ANDROID__
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#endif



struct GamePadButtonState{
    int buttonCode = 0;
    long time = 0;
    bool isPressed = false;
};

class GamePadInput{
public:
    const static long REPEAT_DUR_MILLS = 100; 

    GamePadInput();

    void updateButtonState();

    ~GamePadInput();

    void postPressdEvent(int glfwButtonCode);
    void postReleaseEvent(int glfwButtonCode);
    void postRepeatEvent(int glfwButtonCode);

private:
    std::unordered_map<int, GamePadButtonState> buttonStates;

    // void buttonIsPressed(int button);

    void initButtons();

    std::vector<int> listenButtonTypes = {
        GLFW_GAMEPAD_BUTTON_A,
        GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
        GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        GLFW_GAMEPAD_BUTTON_DPAD_UP,
        GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        // GLFW_GAMEPAD_BUTTON_BACK,
        GLFW_GAMEPAD_BUTTON_START,
    };

    int convertGlfwCode(int glfwButtonCode);
};



