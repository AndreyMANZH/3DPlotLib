#include "Line.h"

Line::Line(Point* p1, Point* p2):
    m_p1(p1), m_p2(p2)
{ }

Line::~Line() 
{
    delete m_p1;
    delete m_p2;
}

Point* Line::get_first() const
{
    return m_p1;
}

Point* Line::get_second() const
{
    return m_p2;
}
