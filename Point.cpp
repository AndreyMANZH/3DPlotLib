#include "Point.h"

Point::Point() : 
	m_x(0), m_y(0), m_z(0),
	m_r(0), m_g(0), m_b(0)
{}


Point::Point(const Point& p) :
	m_x(p.m_x), m_y(p.m_y), m_z(p.m_z),
	m_r(p.m_r), m_g(p.m_g), m_b(p.m_b)
{}


Point::Point(double x, double y, double z, double r, double g, double b) :
	m_x(x), m_y(y), m_z(z),
	m_r(r), m_g(g), m_b(b)	
{ }

Point::Point(Point* p):
	m_x(p->m_x), m_y(p->m_y),
	m_z(p->m_z), m_r(p->m_r),
	m_g(p->m_g), m_b(p->m_b)
{ }

Point::~Point(){}


void Point::set_x(double x)
{
	m_x = x;
}

void Point::set_y(double y)
{
	m_y = y;
}

void Point::set_z(double z)
{
	m_z = z;
}

double Point::get_x() const
{
	return m_x;
}

double Point::get_y() const
{
	return m_y;
}

double Point::get_z() const
{
	return m_z;
}

double Point::get_r() const
{
	return m_r;
}

double Point::get_g() const
{
	return m_g;
}

double Point::get_b() const
{
	return m_b;
}