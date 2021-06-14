#ifndef F_H
#define F_H
#include "math.h"
typedef double (*myfunc) (double, double);

class Function
{
public:
    Function()
    {
        arr[0] = &f1;
        arr[1] = &f2;
        arr[2] = &f3;
        arr[3] = &f4;
        arr[4] = &f5;
        arr[5] = &f6;
    }

    myfunc get_f(int i)
    {
        return arr[i];
    }
private:
    myfunc arr[10];
    static double f1(double x, double y)
    {
        return cos(x)*cos(x) - sin(y)*sin(y);
    }
    static double f2(double x, double y)
    {
        return cos(x)*sin(y);
    }
    static double f3(double x, double y)
    {
        return exp(cos(x));
    }
    static double f4(double x, double y)
    {
        return x*x + y*y;
    }
    static double f5(double x, double y)
    {
        return fabs(cos(x)*x + cos(y)*y);
    }
    static double f6(double x, double y)
    {
        return fabs(cos(x)-sin(y));
    }


};
#endif // F_H
