#include "PointSeries.h"


PointSeries::PointSeries()
	: m_vector_points(new std::vector<Point*>)
{	}

PointSeries::~PointSeries()
{
	delete m_vector_points;
}

void PointSeries::add_point(Point* p)
{
	m_vector_points->push_back(p);	
}

Point* PointSeries::operator[](std::size_t  index)
{
	return m_vector_points->at(index);
}

std::size_t PointSeries::get_size() const
{
	return m_vector_points->size();
}
