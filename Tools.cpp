#include "Tools.h"
// Описание функция пространства math_tools
double math_tools::data_normalize(double data, double min, double mid, double max)
{
    double data_norm = 0;
    
    if (data > mid)
        data_norm = (mid - data) / (-1 * (mid - min));
    else
        data_norm = (data - mid) / (max - mid);

    return data_norm;
}

double math_tools::round(double data, int rest)
{
    return std::round(data * rest) / rest;
}

double math_tools::grad_to_rad(double grad)
{
    return grad*3.14159265/180;
}
// Описание функция пространства paint_tools
void paint_tools::paint_line(Point &&p1, Point &&p2, double line_w)
{
    glColor3f(0.24, 0.24, 0.24);
    glLineWidth(line_w);
    glBegin(GL_LINES);
    glVertex3f(p1.get_x(), p1.get_y(), p1.get_z());
    glVertex3f(p2.get_x(), p2.get_y(), p2.get_z());
    glEnd();
    glLineWidth(1);	
}
void paint_tools::paint_square(Point &&p1, Point &&p2, Point &&p3, Point &&p4)
{
    glColor3f(0.92, 0.92, 0.92);
    glBegin(GL_QUADS);
    glVertex3f(p1.get_x(), p1.get_y(), p1.get_z());
    glVertex3f(p2.get_x(), p2.get_y(), p2.get_z());
    glVertex3f(p3.get_x(), p3.get_y(), p3.get_z());
    glVertex3f(p4.get_x(), p4.get_y(), p4.get_z());
    glEnd();
}