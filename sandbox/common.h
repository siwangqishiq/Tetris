#pragma once

enum CubeColor{
    Yellow = 0,
    Cyan = 1,
    Red = 2,
    Blue = 3,
    Green = 4,
    Orange = 5,
    Purple = 6,
    Gray = 7,
    End = 8
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



