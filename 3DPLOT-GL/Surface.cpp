#include "Surface.h"
#include "Point.h"
Surface::Surface()
{
	this->vector_surface = new std::vector<std::vector<Point>*>;
}
Surface::~Surface()
{
	for (int i = 0; i < this->vector_surface->size(); ++i)
	{
		delete this->vector_surface->at(i);
	}
	delete this->vector_surface;
}
void Surface::push_back(Surface::SurfaceRow* row)
{
	this->vector_surface->push_back(row->get_rowdata());
	// ����������� ���������� ����� �����������
	this->point_count += row->get_points_count();
}
int Surface::getSize()
{
	return this->vector_surface->size();
}
int Surface::get_points_count()
{
	return this->point_count;
}
std::vector<Point>* Surface::operator[](int index)
{
	return this->vector_surface->at(index);
}

// ���������� ��������������� ��������� = ��� �����������
Surface::SurfaceRow::SurfaceRow()
{
	this->vector_row = new 	std::vector<Point>;
}
Surface::SurfaceRow::~SurfaceRow()
{
	delete this->vector_row;
}

void Surface::SurfaceRow::push_back(Point& point)
{
	this->vector_row->push_back(point);
}
int Surface::SurfaceRow::get_points_count()
{
	return this->vector_row->size();
}
Point& Surface::SurfaceRow::operator[](int index)
{
	return this->vector_row->at(index);
}
std::vector<Point>* Surface::SurfaceRow::get_rowdata()
{
	return this->vector_row;
}