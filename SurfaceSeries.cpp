#include "SurfaceSeries.h"

SurfaceSeries::SurfaceSeries():
	m_vector_surfaces(nullptr), m_points_count(0)
{	
	m_vector_surfaces = new std::vector<Surface*>;
}

SurfaceSeries::~SurfaceSeries()
{
	for(std::size_t i = 0; i < m_vector_surfaces->size(); ++i)
		delete m_vector_surfaces->at(i);
	
	delete m_vector_surfaces;
}

void SurfaceSeries::add_surface(Surface* surface)
{
	m_vector_surfaces->push_back(surface);
	m_points_count += surface->get_points_count();
}

Surface* SurfaceSeries::operator[](int index)
{
	return m_vector_surfaces->at(index);
}
std::size_t SurfaceSeries::get_size()
{
	return m_vector_surfaces->size();
}
std::size_t SurfaceSeries::get_points_count()
{
	return m_points_count;
}