#pragma once
#include <vector>
#include "Tools.h"
#include "Point.h"
/*
* ѕринцип построени€ поверхности следующий
* данные о поверхности пишутс€ по р€дам 
*/
class Surface
{
private:
	
	std::vector<std::vector<Point>*>* vector_surface;
	int point_count = 0;
public:
	struct SurfaceRow
	{
		std::vector<Point>* vector_row;
		SurfaceRow();
		~SurfaceRow();

		void push_back(Point& point);
		
		int get_points_count();								//  оличество точек в р€де поверхности

		Point& operator[](int index);
		std::vector<Point>* get_rowdata();
	};

	Surface();
	~Surface();
	void push_back(Surface::SurfaceRow* row);
	std::vector<Point>* operator[](int index);
	
	int getSize();											//  оличество р€дов
	int get_points_count();									//  оличество точек поверхности
};

