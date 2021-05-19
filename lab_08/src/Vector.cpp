//
// Created by denis on 15.05.2021.
//

#include "../inc/Vector.h"

Vector::Vector(double inX, double inY) {
    x = inX;
    y = inY;
}

Vector::Vector(dot_t A, dot_t B) {
    x = B.first - A.first;
    y = B.second - A.second;
}

double Vector::getX() const {
    return x;
}

double Vector::getY() const {
    return y;
}

void Vector::Negative() {
    x = -x;
    y = -y;
}

void Vector::Multiplication(double value) {
    x *= value;
    y *= value;
}

double Vector::Multiplication(const Vector &A, const Vector &B) {
    return A.x * B.y - A.y * B.x;
}

double Vector::Scalar(const Vector &A, const Vector &B) {
    return A.x * B.x + A.y * B.y;
}

void Vector::setX(double inX) {
    x = inX;
}

void Vector::setY(double inY) {
    y = inY;
}
