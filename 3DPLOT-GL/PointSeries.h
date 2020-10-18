#pragma once
#include "Point.h"
#include <vector>
class PointSeries
{
public:
	PointSeries();
	~PointSeries();
	void push_back(Point& p);
	
	Point& operator[](int index);

	static double getMax();
	int getSize();
private:
	std::vector<Point>* vector_points;
	static double max;							// ћаксимальное значение необходимое дл€ нормализации данных в диапазон (-1...1)
};

