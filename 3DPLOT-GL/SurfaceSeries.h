#pragma once
#include <vector>
#include "Surface.h"
class SurfaceSeries
{
public:
	SurfaceSeries();
	~SurfaceSeries();
	void push_back(Surface* surface);
	Surface* operator[](int index);
	int getSize();								// ���������� ������������
	int get_points_count();
private:
	std::vector<Surface*>* vector_surfaces;
	int points_count = 0;						// ���������� ���� ����� ������������
	int array_size = 0;
};

