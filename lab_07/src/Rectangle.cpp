//
// Created by denis on 20.05.2021.
//

#include "../inc/Rectangle.h"

Rectangle::Rectangle(dot_t start, int width, int height) {
    A = start;
    B = dot_t(start.first + width, start.second + height);

}

unsigned int Rectangle::getCode(dot_t point) const {
    unsigned int sum = 0b0000;
    if (point.first < A.first)
        sum |= 0b1000u;
    if (point.first > B.first)
        sum |= 0b0100u;
    if (point.second < A.second)
        sum |= 0b0010u;
    if (point.second > B.second)
        sum |= 0b0001u;
    return sum;
}

bool Rectangle::isLineVisible(unsigned int t0, unsigned int t1) {
    return ((t0 | t1) == 0);
}

bool Rectangle::isTrivialInvisible(unsigned int t0, unsigned int t1) {
    return ((t0 & t1) != 0);
}

int Rectangle::getCoord(int index) const {
    if (index == 0)
        return A.first;
    else if (index == 1)
        return B.first;
    else if (index == 2)
        return A.second;
    else if (index == 3)
        return B.second;
    else
        return -1;
}
