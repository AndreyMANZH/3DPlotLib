#include "LineSeries.h"
#include <vector>

double LineSeries::max = 0;

LineSeries::LineSeries()
{
	vector_lines = new std::vector<LineSeries::Line>;
}
LineSeries::~LineSeries()
{
	delete vector_lines;
}

void LineSeries::push_back(LineSeries::Line line)
{
	this->setMax(line.p1);
	this->setMax(line.p2);
	this->vector_lines->push_back(line);
}

LineSeries::Line& LineSeries::operator[](int index)
{
	return vector_lines->at(index);
}

double LineSeries::getMax()
{
	return LineSeries::max;
}

int LineSeries::getSize()
{
	return this->vector_lines->size();
}

void LineSeries::setMax(Point& p)
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

	if (_max > LineSeries::max)
		LineSeries::max = _max;
}

LineSeries::Line::Line()
{
  //
}

LineSeries::Line::Line(Point& p1, Point& p2)
{
	this->p1 = p1;
	this->p2 = p2;
}
LineSeries::Line::~Line()
{
	//
}