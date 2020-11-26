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

double round(double data, int rest)
{

	return round(data * rest) / rest;
}
void norm_vector(double A[3], double B[3], double C[3], double N[3])
{
	double a[3] = { A[0] - B[0], A[1] - B[1], A[2] - B[2] };
	double b[3] = { A[0] - C[0], A[1] - C[1], A[2] - C[2] };
	double max = 1;

	N[0] = a[1] * b[2] - b[1] * a[2];
	N[1] = a[2] * b[0] - b[2] * a[0];
	N[2] = a[0] * b[1] - b[0] * a[1];
	
	/*if (N[0] > 1 && N[0] > N[1] && N[0] > N[2])
	{ 
		max = N[0];
		N[0] = N[0] / max;
		N[1] = N[1] / max;
		N[2] = N[2] / max;
		return;
	}
	if (N[1] > 1 && N[1] > N[0] && N[1] > N[2])
	{
		max = N[1];
		N[0] = N[0] / max;
		N[1] = N[1] / max;
		N[2] = N[2] / max;
		return;
	}
	if (N[2] > 1 && N[2] > N[1] && N[2] > N[0])
	{
		max = N[2];
		N[0] = N[0] / max;
		N[1] = N[1] / max;
		N[2] = N[2] / max;
		return;
	}*/
}