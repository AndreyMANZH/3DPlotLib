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
}

Surface* SurfaceSeries::operator[](int index)
{
	return this->vector_surfaces->at(index);
}
int SurfaceSeries::getSize()
{
	return this->vector_surfaces->size();
}