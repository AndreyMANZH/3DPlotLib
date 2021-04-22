#include "Tools.h"
// Описание функция пространства math_tools
double math_tools::data_normalize(double data, double min, double mid, double max)
{
    double _x = 0;
    
    if (data > mid)
        _x = (mid - data) / (-1 * (mid - min));
    else
        _x = (data - mid) / (max - mid);

    return _x;
}

double math_tools::round(double data, int rest)
{
    return std::round(data * rest) / rest;
}
// Описание функция пространства paint_tools
void paint_tools::paint_line(Point p1, Point p2, double line_w)
{
    	glColor3f(0.24, 0.24, 0.24);
		glLineWidth(line_w);
		glBegin(GL_LINES);
		glVertex3f(p1.get_x(), p1.get_y(), p1.get_z());
		glVertex3f(p2.get_x(), p2.get_y(), p2.get_z());
		glEnd();
		glLineWidth(1);	
}