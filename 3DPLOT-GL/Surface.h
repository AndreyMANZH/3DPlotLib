#pragma once
#include <vector>
#include "Tools.h"
#include "Point.h"
/*
* ������� ���������� ����������� ���������
* ������ � ����������� ������� �� ����� 
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
		
		int get_points_count();								// ���������� ����� � ���� �����������

		Point& operator[](int index);
		std::vector<Point>* get_rowdata();
	};

	Surface();
	~Surface();
	void push_back(Surface::SurfaceRow* row);
	std::vector<Point>* operator[](int index);
	
	int getSize();											// ���������� �����
	int get_points_count();									// ���������� ����� �����������
};

