//
// Created by denis on 15.05.2021.
//

#ifndef LAB_08_VECTOR_H
#define LAB_08_VECTOR_H

#include "vector"

typedef std::pair<int, int> dot_t;
typedef std::vector<dot_t> line_t;
class Vector {
public:

    explicit Vector(double inX = 0, double inY = 0);
    Vector(dot_t A, dot_t B);

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    void setX(double inX);
    void setY(double inY);

    void Negative();
    void Multiplication(double value);
    static double Multiplication(const Vector& A, const Vector& B);
    static double Scalar(const Vector& A, const Vector& B);

private:

    double x;
    double y;


};


#endif //LAB_08_VECTOR_H
