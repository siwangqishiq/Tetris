
#include "shape/shape.h"

Shape::Shape(){
}

void Shape::reset(){
    dy = 0;
    dx = 0;
}

std::vector<int> Shape::getPoints(){
    return this->points;
}

Shape::~Shape(){
}
