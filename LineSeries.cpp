#include "LineSeries.h"


LineSeries::LineSeries():
	m_vector_lines(new std::vector<Line*>)
{

}

LineSeries::~LineSeries()
{
	for (std::size_t i = 0; i < m_vector_lines->size(); ++i)
		delete m_vector_lines->at(i);
	
	delete m_vector_lines;
}

void LineSeries::add_line(Line *l)
{
	m_vector_lines->push_back(l);
}

Line* LineSeries::operator[](std::size_t index)
{
	return m_vector_lines->at(index);
}

std::size_t LineSeries::get_size() const
{
	return m_vector_lines->size();
}

