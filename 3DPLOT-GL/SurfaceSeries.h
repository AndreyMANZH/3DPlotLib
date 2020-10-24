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
	int getSize();
private:
	std::vector<Surface*>* vector_surfaces;
};

