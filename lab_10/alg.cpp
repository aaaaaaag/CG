#include "alg.h"
#include <vector>
#include <QPoint>
#include <QDebug>


#define WINDOW_WIDTH 900
#define PI 3.14

int sign(int n)
{
    if (n > 0)
        return 1;
    else if (n == 0)
        return 0;
    return -1;
}

int is_visible(int x, int y, std::vector<int> &top, std::vector<int> &down)
{
    if (x > WINDOW_WIDTH || x < 0) return 0;
    if (y < top[x] && y > down[x]) return 0;
    if (y >= top[x]) return 1;
    return -1;
}

void horizon(int x1, int y1, int x2, int y2, std::vector<int> &top, std::vector<int> &down, QPainter &painter)
{

    if (x2 < x1)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }
    if (x1 > WINDOW_WIDTH || x1 < 0)
    {
        qDebug() << "вышли за границы в горизонте";
        return;
    }
    if (x2 == x1)
    {
        top[x2] = qMax(top[x2],y2);
        down[x2] = qMin(down[x2],y2);
        if (x2 >= 0 && x2 <= WINDOW_WIDTH)
        {
            painter.drawLine(x1,y1,x2,y2);
        }
    }
    else
    {
        int x_prev = x1;
        int y_prev = y1;
        double m = (y2-y1)/(double)(x2-x1);
        for (int x = x1; x < x2 && x < WINDOW_WIDTH; x++)
        {
            int y = round(m * (x - x1)+y1);
            top[x] = qMax(top[x],y);
            down[x] = qMin(down[x],y);
            if (x >= 0 && x <= WINDOW_WIDTH)
            {
                painter.drawLine(x_prev, y_prev,x,y);
            }
            //x_prev = x;
            //y_prev = y;
        }
    }
}

void EdgeWhatcher(int &x, int &y, int &edgex, int &edgey,  std::vector<int> &top, std::vector<int> &down, QPainter &painter)
{
    if (edgex != -1)
    {
        horizon(edgex,edgey,x,y,top,down,painter);
    }
    edgex = x;
    edgey = y;
}

QPoint FindIntersection(int x1, int y1, int x2, int y2, std::vector<int> &vector)
{
    QPoint a(x1,y1);
    int dx = x2 - x1;
    int dy_c = y2 - y1; //сurrent
    if (x1 > WINDOW_WIDTH || x2 > WINDOW_WIDTH || x1 < 0 || x2 < 0)
    {
        qDebug() << "вышли за границы поля при поиске пересечения";
        return a;
    }
    int vx1 = vector[x1];
    int vx2 = vector[x2];
    int dy_p = vx2- vx1; //previous
    double m = dy_c/(double)dx;
    if (dx == 0)
    {
        a.setX(x2);
        a.setY(vx2);
    }
    else if (y1 == vx1  && y2 == vx2)
    {
        a.setX(x1);
        a.setY(y1);
    }
    else
    {
        if (dy_c != dy_p)
        {
            a.setX(x1 - round(dx*(y1 - vx1)/(double)(dy_c - dy_p)));
            a.setY(round((a.x() - x1)*m + y1));
        }
        else
        {

            qDebug() << "dy_c == dy_p";
        }
    }
    return a;
}

void rotate_x(double &y, double &z, double tetax)
{
    tetax = tetax * PI / 180;
    double buf = y;
    y = cos(tetax) * y - sin(tetax) * z;
    z = cos(tetax) * z + sin(tetax) * buf;
}
void rotate_y(double &x, double &z, double tetay)
{
    tetay = tetay * PI / 180;
    double buf = x;
    x = cos(tetay) * x - sin(tetay) * z;
    z = cos(tetay) * z + sin(tetay) * buf;
}
void rotate_z(double &x, double &y, double tetaz)
{
    tetaz = tetaz * PI / 180;
    double buf = x;
    x = cos(tetaz) * x - sin(tetaz) * y;
    y = cos(tetaz) * y + sin(tetaz) * buf;
}
void transform(double &x, double &y, double &z, double tetax, double tetay, double tetaz, int &res_x, int &res_y)
{
    double x_center = WINDOW_WIDTH / 2;
    double y_center = WINDOW_WIDTH / 2 ;
    double x_tmp = x;
    double y_tmp = y;
    double z_tmp = z;
    rotate_x(y_tmp, z_tmp, tetax);
    rotate_y(x_tmp, z_tmp, tetay);
    rotate_z(x_tmp, y_tmp, tetaz);
    res_x = static_cast<int>(round(x_tmp * 48 + x_center));
    res_y = static_cast<int>(round(y_tmp * 48 + y_center));
}

void horizon_alg(params Params, QPainter &painter)
{
    //#define WINDOW_WIDTH 700
    std::vector<int> top(WINDOW_WIDTH, 0);
    std::vector<int> down(WINDOW_WIDTH, WINDOW_WIDTH);

    double x, y_p;
    int T, P;

    QPoint i;
    int x_prev, y_prev;
    int x_left = -1;
    int y_left = -1;
    int x_right = -1;
    int y_right = -1;

    for(double z = Params.zend; z >= Params.zbegin; z -= Params.zdelta)
    {
        double nz = z;
        if ((Params.alphax > 90 || Params.alphax < -90) && (Params.alphay > 90 || Params.alphay < -90))
            nz = z;
        else if (Params.alphax > 90 || Params.alphax < -90)
            nz = (Params.zend - z) + Params.zbegin;
        else if (Params.alphay > 90 || Params.alphay < -90)
            nz = (Params.zend - z) + Params.zbegin;
        y_p = Params.func(Params.xbegin,nz);
        transform(Params.xbegin, y_p, nz, Params.alphax, Params.alphay, Params.alphaz, x_prev, y_prev);
        EdgeWhatcher(x_prev,y_prev,x_left,y_left,top,down,painter);
        P = is_visible(x_prev,y_prev,top,down);
        for (x = Params.xbegin; x <= Params.xend; x += Params.xdelta)
        {
            y_p = Params.func(x,nz);
            int curr_x, curr_y;
            transform(x, y_p, nz, Params.alphax, Params.alphay, Params.alphaz,curr_x , curr_y);
            T = is_visible(curr_x,curr_y,top,down);
            if (T == P)
            {
                if (T == 1 || T == -1)
                {
                    horizon(x_prev, y_prev, curr_x,curr_y,top,down,painter);
                }
            }
            else if (T == 0)
            {
                if (P == 1)
                {
                    i = FindIntersection(x_prev, y_prev,curr_x,curr_y,top);
                }
                else
                {
                    i = FindIntersection(x_prev, y_prev,curr_x,curr_y,down);
                }
                horizon(x_prev, y_prev,i.x(),i.y(),top,down,painter);
            }
            else if (T == 1)
            {
                if (P == 0)
                {
                     i = FindIntersection(x_prev, y_prev,curr_x,curr_y,top);
                     horizon(x_prev, y_prev,i.x(),i.y(),top,down,painter);
                }
                else
                {
                    i = FindIntersection(x_prev, y_prev,curr_x,curr_y,top);
                    horizon(x_prev, y_prev,i.x(),i.y(),top,down,painter);
                    i = FindIntersection(x_prev, y_prev,curr_x,curr_y,down);
                    horizon(i.x(), i.y(),curr_x,curr_y,top,down,painter);
                }
            }
            else
            {
                if (P == 0)
                {
                     i = FindIntersection(x_prev, y_prev,curr_x,curr_y,down);
                     horizon(x_prev, y_prev,i.x(),i.y(),top,down,painter);
                }
                else
                {
                    i = FindIntersection(x_prev, y_prev,curr_x,curr_y,top);
                    horizon(x_prev, y_prev,i.x(),i.y(),top,down,painter);
                    i = FindIntersection(x_prev, y_prev,curr_x,curr_y,down);
                    horizon(i.x(), i.y(),curr_x,curr_y,top,down,painter);
                }
            }
            P = T;
            x_prev = curr_x;
            y_prev = curr_y;
        }
        EdgeWhatcher(x_prev, y_prev,x_right, y_right,top,down,painter);
    }
}




