#include "SurfaceSeries.h"
SurfaceSeries::SurfaceSeries()
{
	this->vector_surfaces = new std::vector<Surface*>;
}
SurfaceSeries::~SurfaceSeries()
{
	delete this->vector_surfaces;
}

void SurfaceSeries::push_back(Surface* surface)
{
	this->vector_surfaces->push_back(surface);
	//Увеличиваем количество точек
	this->points_count += surface->get_points_count();
}

Surface* SurfaceSeries::operator[](int index)
{
	return this->vector_surfaces->at(index);
}
int SurfaceSeries::getSize()
{
	return this->vector_surfaces->size();
}
int SurfaceSeries::get_points_count()
{
	return this->points_count;
}