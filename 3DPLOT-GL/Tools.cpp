#include "Tools.h"
#include <cmath>

double dataNormalize(double data, double min, double mid, double max)
{
	double _x = 0;
	
	if (data > mid)
		_x = (mid - data) / (-1 * (mid - min));
	else
		_x = (data - mid) / (max - mid);

	return _x;
}

bool isClose(double data1, double data2, double absTolerance)
{
	return abs(data1 - data2) <= absTolerance;
}
