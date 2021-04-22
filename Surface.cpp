#include "Surface.h"
#include <iostream>
Surface::Surface():
	m_vector_surface(new std::vector<Surface::SurfaceRow*>(0)), m_point_count(0)
{	
	std::cout << " Surface init" << std::endl;
}
Surface::~Surface()
{
	
	if (m_vector_surface != nullptr)
	{
		std::cout << " ENDL " << get_size() << std::endl;
		for (std::size_t i = 0; i < get_size(); ++i)
		{
			if (m_vector_surface->at(i) != nullptr)
			{
				delete m_vector_surface->at(i);
				m_vector_surface->at(i) = nullptr;
			}
		}
		
		delete m_vector_surface;
		m_vector_surface = nullptr;

	}

}
void Surface::add_surface_row(Surface::SurfaceRow* row)
{
	m_vector_surface->push_back(row);
	
	m_point_count += row->get_size();
}
std::size_t Surface::get_size() const
{
	return m_vector_surface->size();
}
std::size_t Surface::get_points_count() const
{
	return m_point_count;
}
Surface::SurfaceRow* Surface::operator[](const std::size_t index)
{
	return (*m_vector_surface)[index];
}

// Определение элементов класса SurfaceRow
//--------------------------------------------------------------------------------------------
Surface::SurfaceRow::SurfaceRow():
	m_vector_row(nullptr)
{
	m_vector_row = new std::vector<Point*>;
}


Surface::SurfaceRow::~SurfaceRow()
{
	if (m_vector_row != nullptr)
	{
		for(std::size_t i = 0; i < m_vector_row->size(); ++i)
		{
			if (m_vector_row->at(i) != nullptr)
			{
				delete m_vector_row->at(i);
				m_vector_row = nullptr;
			}
			
		}
		delete m_vector_row;
		m_vector_row = nullptr;
	}
}

void Surface::SurfaceRow::add_point(Point* point)
{
	m_vector_row->push_back(point);
}
std::size_t Surface::SurfaceRow::get_size() const
{
	return m_vector_row->size();
}
Point* Surface::SurfaceRow::operator[](std::size_t index)
{
	return (*m_vector_row)[index];
}