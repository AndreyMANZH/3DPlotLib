#pragma once
#include "Point.h"
#include <vector>
class LineSeries
{
public:
	class Line
	{
	public:
		Line();
		Line(Point& p1, Point& p2);
		~Line();

		Point p1;
		Point p2;
	};
	LineSeries();
	~LineSeries();

	void push_back(Line line);

	LineSeries::Line& operator[](int index);

	static double getMax();
	int getSize();

private:
	std::vector<Line>* vector_lines;

	void setMax(Point& p);

	static double max;
};

