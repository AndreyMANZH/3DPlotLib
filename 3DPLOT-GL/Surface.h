#pragma once
#include <vector>
#include "Tools.h"
#include "Point.h"
/*
* Принцип построения поверхности следующий
* данные о поверхности пишутся по рядам 
*/
class Surface
{
private:
	
	std::vector<std::vector<Point>*>* vector_surface;
public:
	struct SurfaceRow
	{
		std::vector<Point>* vector_row;
		SurfaceRow();
		~SurfaceRow();

		void push_back(Point& point);
		Point& operator[](int index);
		std::vector<Point>* getRowData();
	};

	Surface();
	~Surface();
	void push_back(Surface::SurfaceRow* row);
	std::vector<Point>* operator[](int index);
	int getSize();
};

