#pragma once
/*
* ������������ ������ � ������ [-1; 1]
* data - �������� ������� ������������ ������������
* min - ����������� ������� ��� ��������� � ������� ��������� data
* mid - ������� ��������  ��� ��������� � ������� ��������� data
* max - ������������ ��������  ��� ��������� � ������� ��������� data
*/
#define GRAD(X) X*3.14159265/180

double dataNormalize(double data, double min, double mid, double max);
/*
* ������� isClose ������������� ��� ��������� ������
*/
template <typename T>
bool isClose(T data1, T data2, double absTolerance=0.0001)
{
	return abs(data1 - data2) <= absTolerance;
}
/*
* ������� round ������������� ��� ���������� ������
* data - �������� ������� ������������ ����������
* rest - ������� ����� �����
*/
double round(double data, int rest);

/*
* ������ ������� � ����������� ������������
*/
void norm_vector(double A[3], double B[3], double C[3], double N[3]);