
#include "shape/shape.h"
#include <iostream>

Shape::Shape(){
}

void Shape::reset(){
    dy = 0;
    dx = 0;
}

void Shape::moveLeft(){
    // std::cout << "moveLeft " << std::endl;
    dx--;
}

void Shape::moveRight(){
    // std::cout << "moveRight " << std::endl;
    dx++;
}

void Shape::moveDown(){
    // std::cout << "moveDown " << std::endl;
    dy++;
}

std::vector<int> Shape::getPoints(){
    const int size = points.size();
    std::vector<int> result(size);
    // for(auto &v : points){
    //     std::cout << v << " ";
    // }
    // std::cout << std::endl;
    for(int i = 0, len = (size >> 1) ; i < len ; i++){
        // std::cout << "--> " << points[2 * i + 0] + dRow << std::endl;
        result[2 * i + 0] = points[2 * i + 0] + dy;
        result[2 * i + 1] = points[2 * i + 1] + dx;
    }//end for i

    // for(auto &v : result){
    //     std::cout << v << " ";
    // }
    // std::cout << std::endl;
    
    return result;
}

Shape::~Shape(){
}
