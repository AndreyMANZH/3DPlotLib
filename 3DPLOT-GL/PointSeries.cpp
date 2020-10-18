#include "PointSeries.h"
#include <cmath>

// Определение статических переменных
double PointSeries::max = 0;
PointSeries::PointSeries()
{
	vector_points = new std::vector<Point>;
}
PointSeries::~PointSeries()
{
	delete vector_points; // Осторожно!!!!
}

void PointSeries::push_back(Point& p)
{
	double x = abs(p.getX());
	double y = abs(p.getY());
	double z = abs(p.getZ());
	double _max = 0;
	if (x > y && x > z)
		_max = x;
	else if (y > x && y > z)
		_max = y;
	else if (z > x && z > y)
		_max = z;
	if (_max > PointSeries::max)
		PointSeries::max = _max;
	this->vector_points->push_back(p);

}

Point& PointSeries::operator[](int index)
{
	return this->vector_points->at(index);
}

double PointSeries::getMax()
{
	return PointSeries::max;
}

int PointSeries::getSize()
{
	return this->vector_points->size();
}