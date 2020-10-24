#include "Point.h"
Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
}
Point::Point(const Point& p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	this->r = p.r;
	this->g = p.g;
	this->b = p.b;
}
Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = 0;
	this->g = 0;
	this->b = 0;
}
Point::Point(double x, double y, double z, double r, double g, double b) : Point(x, y, z)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
Point::~Point()
{
	//
}


void Point::setX(double x)
{
	this->x = x;
}
void Point::setY(double y)
{
	this->y = y;
}
void Point::setZ(double z)
{
	this->z = z;
}

double Point::getX()
{
	return this->x;
}
double Point::getY()
{
	return this->y;
}
double Point::getZ()
{
	return this->z;
}