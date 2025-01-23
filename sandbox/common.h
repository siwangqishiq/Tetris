#pragma once
#include "glm/vec4.hpp"

const glm::vec4 ColorTextSelected = glm::vec4(1.0f , 1.0f , 1.0f , 1.0f);
const glm::vec4 ColorTextUnselected = glm::vec4(1.0f , 1.0f , 1.0f , 0.3f);

enum CubeColor{
    Yellow = 1,
    Cyan = 2,
    Red = 3,
    Blue = 4,
    Green = 5,
    Orange = 6,
    Purple = 7,
    Gray = 8,
    End = 9
};


/**
 *  0 0 0 0
 *  
 * 
 */
const int TETRIS_TYPE_I = 1;//Cyan

/**
 *    0
 *    0
 *  0 0
 */
const int TETRIS_TYPE_J =2;//Blue


/**
 *  0
 *  0
 *  0 0 
 */
const int TETRIS_TYPE_L = 3;// Orange


/**
 * 0 0
 * 0 0
 */
const int TETRIS_TYPE_O = 4;// Yellow

/**
 *    0 0
 *  0 0   
 */
const int TETRIS_TYPE_S = 5;// Green

/**
 *  0 0 0 
 *    0 
 */
const int TETRIS_TYPE_T = 6;//Purple

/**
 * 0 0
 *   0 0
 */
const int TETRIS_TYPE_Z = 7;//Red



