//
// Created by denis on 20.05.2021.
//

#ifndef LAB_07_RECTANGLE_H
#define LAB_07_RECTANGLE_H


#include <utility>

typedef std::pair<int, int> dot_t;
class Rectangle {
public:
    Rectangle(dot_t start, int width, int height);

    [[nodiscard]] unsigned int getCode(dot_t point) const;

    static bool isLineVisible(unsigned int t0, unsigned int t1);

    static bool isTrivialInvisible(unsigned int t0, unsigned int t1);

    int getCoord(int index) const;


private:

    dot_t A;
    dot_t B;


};


#endif //LAB_07_RECTANGLE_H
