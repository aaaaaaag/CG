#ifndef ALG_H
#define ALG_H
#include "f.h"
#include <QPainter>

struct params
{
    params(double xb, double xe, double xd, double yb, double ye, double yd):
      xbegin(xb),
      xend(xe),
      xdelta(xd),
      zbegin(yb),
      zend(ye),
      zdelta(yd)
    {}
    double xbegin;
    double xend;
    double xdelta;
    double zbegin;
    double zend;
    double zdelta;

    myfunc func;

    double alphax;
    double alphay;
    double alphaz;
};

typedef struct point point_t;
struct point
{
    point():X(0),Y(0),Z(0){}
    point(double x, double y): X(x), Y(y), Z(0){}
    point(double x, double y, double z):X(x),Y(y),Z(z){}
    point(const point &p)
    {
        this->X = p.x();
        this->Y = p.y();
        this->Z = p.z();
    }
    double X;
    double Y;
    double Z;

    double x() const {return this->X;}
    double y() const {return this->Y;}
    double z() const {return this->Z;}
    void setY(double y){this->Y = y;}
    void setX(double x){this->X = x;}
    void setZ(double z){this->Z = z;}

    point_t& operator =(const point_t &p)
    {
        this->X = p.x();
        this->Y = p.y();
        this->Z = p.z();
        return *this;
    }
};

void horizon_alg(params Params, QPainter &painter);

#endif // ALG_H
